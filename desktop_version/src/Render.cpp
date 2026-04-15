#include <SDL.h>

#include "ActionSets.h"
#include "ButtonGlyphs.h"
#include "Constants.h"
#include "Credits.h"
#include "CustomLevels.h"
#include "Editor.h"
#include "Entity.h"
#include "FileSystemUtils.h"
#include "Font.h"
#include "GlitchrunnerMode.h"
#include "Graphics.h"
#include "GraphicsUtil.h"
#include "InterimVersion.h"
#include "KeyPoll.h"
#include "LevelDebugger.h"
#include "Localization.h"
#include "LocalizationStorage.h"
#include "MakeAndPlay.h"
#include "Map.h"
#include "Maths.h"
#include "Music.h"
#include "ReleaseVersion.h"
#include "RoomnameTranslator.h"
#include "Screen.h"
#include "Script.h"
#include "UtilityClass.h"
#include "VFormat.h"

static int tr;
static int tg;
static int tb;

struct MapRenderData
{
    int zoom;
    int xoff;
    int yoff;
    int legendxoff;
    int legendyoff;
};

static inline void drawslowdowntext(const int y)
{
    switch (game.slowdown)
    {
    case 30:
        font::print_wrap(PR_CEN, -1, y, loc::gettext(STR_ID("Game speed is normal.", STR_SPEED_IS_NORMAL)), tr/2, tg/2, tb/2);
        break;
    case 24:
        font::print_wrap(PR_CEN, -1, y, loc::gettext(STR_ID("Game speed is at 80%", STR_SPEED_IS_80)), tr, tg, tb);
        break;
    case 18:
        font::print_wrap(PR_CEN, -1, y, loc::gettext(STR_ID("Game speed is at 60%", STR_SPEED_IS_60)), tr, tg, tb);
        break;
    case 12:
        font::print_wrap(PR_CEN, -1, y, loc::gettext(STR_ID("Game speed is at 40%", STR_SPEED_IS_40)), tr, tg, tb);
        break;
    }
}

static void slider_get(char* buffer, size_t buffer_len, int position, int n_positions, int target_width)
{
    /* Print a slider to the buffer for target_width in pixels.
     *
     * <--target w-->
     * []............
     * ......[]......
     * ............[]
     * ^^^^^^         dots_per_position=6
     * ^^^^^^^^^^^^^^ max_chars=14
     */

    if (n_positions < 2 || position < 0 || position >= n_positions)
    {
        buffer[0] = '\0';
        return;
    }

    int max_chars = ((target_width - font::len(0, "[]")) / font::len(0, ".")) + 2;
    max_chars = SDL_min(max_chars, buffer_len-1);

    int dots_per_position = (max_chars-2) / (n_positions-1);
    max_chars = dots_per_position * (n_positions-1) + 2;

    VVV_fillstring(buffer, max_chars+1, '.');
    if (dots_per_position<1)
    {
        return;
    }

    int handle_idx = position*dots_per_position;
    buffer[handle_idx] = '[';
    buffer[handle_idx+1] = ']';
}

static void volumesliderrender(void)
{
    int volume_max_position = USER_VOLUME_MAX / USER_VOLUME_STEP;

    int volume;
    switch (game.currentmenuoption)
    {
    case 0:
        volume = music.user_music_volume;
        break;
    case 1:
        volume = music.user_sound_volume;
        break;
    default:
        SDL_assert(0 && "Unhandled volume slider menu option!");
        return;
    }

    char slider[40 + 1];
    slider_get(slider, sizeof(slider), volume_max_position*volume/USER_VOLUME_MAX, volume_max_position+1, 240);

    char buffer[SCREEN_WIDTH_CHARS + 1];

    if (game.slidermode == SLIDER_NONE)
    {
        SDL_strlcpy(buffer, slider, sizeof(buffer));
    }
    else
    {
        /* Draw selection brackets. */
        vformat_buf(buffer, sizeof(buffer), loc::get_langmeta()->menu_select.c_str(), "label:str", slider);
    }

    font::print(PR_CEN, -1, 95, buffer, tr, tg, tb);
}

static void inline drawglitchrunnertext(const int y)
{
    int tempr = tr;
    int tempg = tg;
    int tempb = tb;

    char buffer[SCREEN_WIDTH_CHARS + 1];

    const enum GlitchrunnerMode mode = GlitchrunnerMode_get();

    if (mode == GlitchrunnerNone)
    {
        tempr /= 2;
        tempg /= 2;
        tempb /= 2;

        SDL_strlcpy(buffer, loc::gettext(STR_ID("Glitchrunner mode is OFF", STR_GLITCH_IS_OFF)), sizeof(buffer));
    }
    else
    {
        const char* mode_string = loc::gettext(STR_ID(GlitchrunnerMode_enum_to_string(mode), (String_ID)(STR_GLITCH_NONE + mode)));
        vformat_buf(buffer, sizeof(buffer), loc::gettext(STR_ID("Glitchrunner mode is {version}", STR_GLITCH_IS_VERSION)), "version:str", mode_string);
    }

    font::print_wrap(PR_CEN, -1, y, buffer, tempr, tempg, tempb);
}

static inline void draw_skip_message()
{
    /* Unlock 18 is Flip Mode.
     * If this is the first playthrough, 5 (game completed) will be unlocked
     * but not Flip Mode until the player hits "play" on the title screen */
    bool draw =
#ifndef MAKEANDPLAY
        game.unlock[Unlock_FLIPMODE] &&
#endif
        graphics.fademode == FADE_NONE;
    if (!draw)
    {
        return;
    }

    const int alpha = graphics.lerp(
        game.old_skip_message_timer, game.skip_message_timer
    );

    draw = alpha > 100;
    if (!draw)
    {
        return;
    }

    char buffer[SCREEN_WIDTH_CHARS + 1];
    vformat_buf(
        buffer, sizeof(buffer),
        loc::gettext(STR_ID("- Press {button} to skip -", STR_PROMPT_SKIP)),
        "button:but",
        vformat_button(ActionSet_InGame, Action_InGame_Map)
    );
    font::print(
        PR_BRIGHTNESS(alpha) | PR_BOR | PR_CEN,
        -1, graphics.flipmode ? 20 : 210, buffer,
        220 - help.glow, 220 - help.glow, 255 - help.glow / 2
    );
}

#ifdef __NDS__
static String_ID lang_to_id(const char *langName)
{
    if (strncmp(langName, "Ar", 2) == 0) return STR_ARABIC;
    if (strncmp(langName, "Ca", 2) == 0) return STR_CATALAN;
    if (strncmp(langName, "We", 2) == 0) return STR_WELSH;
    if (strncmp(langName, "Ge", 2) == 0) return STR_GERMAN;
    if (strncmp(langName, "Es", 2) == 0) return STR_ESPERANTO;
    if (strncmp(langName, "Sp", 2) == 0)
    {
        if (langName[9] == 'E') return STR_SPANISH_ES;
        if (langName[9] == 'L') return STR_SPANISH_LATAM;
        if (langName[9] == 'A') return STR_SPANISH_ARG;
        return STR_SPANISH;
    }
    if (strncmp(langName, "Fr", 2) == 0) return STR_FRENCH;
    if (strncmp(langName, "Ir", 2) == 0) return STR_IRISH;
    if (strncmp(langName, "It", 2) == 0) return STR_ITALIAN;
    if (strncmp(langName, "Ja", 2) == 0) return STR_JAPANESE;
    if (strncmp(langName, "Ko", 2) == 0) return STR_KOREAN;
    if (strncmp(langName, "Du", 2) == 0) return STR_DUTCH;
    if (strncmp(langName, "Po", 2) == 0) return STR_POLISH;
    if (strncmp(langName, "Br", 2) == 0) return STR_BRAZIL_PORTUGUESE;
    if (strncmp(langName, "Eu", 2) == 0) return STR_EUROPE_PORTUGUESE;
    if (strncmp(langName, "Ru", 2) == 0) return STR_RUSSIAN;
    if (strncmp(langName, "Si", 2) == 0) return STR_SILESIAN;
    if (strncmp(langName, "Tu", 2) == 0) return STR_TURKISH;
    if (strncmp(langName, "Uk", 2) == 0) return STR_UKRAINIAN;
    if (strncmp(langName, "Ch", 2) == 0)
    {
        if (langName[9] == 'S') return STR_CHINESE_SIMPLE;
        return STR_CHINESE_TRAD;
    }
    return STR_BLANK_0;
}
#endif

static void menurender(void)
{

    switch (game.currentmenuname)
    {
    case Menu::mainmenu:
    {
        const int temp = 50;
        graphics.draw_sprite((160 - 96) + 0 * 32, temp, 23, tr, tg, tb);
        graphics.draw_sprite((160 - 96) + 1 * 32, temp, 23, tr, tg, tb);
        graphics.draw_sprite((160 - 96) + 2 * 32, temp, 23, tr, tg, tb);
        graphics.draw_sprite((160 - 96) + 3 * 32, temp, 23, tr, tg, tb);
        graphics.draw_sprite((160 - 96) + 4 * 32, temp, 23, tr, tg, tb);
        graphics.draw_sprite((160 - 96) + 5 * 32, temp, 23, tr, tg, tb);
#if defined(MAKEANDPLAY)
        font::print(PR_RIGHT, 264, temp+35, loc::gettext(STR_ID("MAKE AND PLAY EDITION", STR_MAKE_AND_PLAY)), tr, tg, tb);
#endif
#ifdef INTERIM_VERSION_EXISTS
        font::print(PR_RIGHT | PR_FONT_8X8, 310, 200, COMMIT_DATE, tr/2, tg/2, tb/2);
        font::print(PR_RIGHT | PR_FONT_8X8, 310, 210, INTERIM_COMMIT, tr/2, tg/2, tb/2);
        font::print(PR_RIGHT | PR_FONT_8X8, 310, 220, BRANCH_NAME, tr/2, tg/2, tb/2);
#endif
        font::print(PR_RIGHT, 310, 230, RELEASE_VERSION, tr/2, tg/2, tb/2);

        const char* left_msg = NULL;

        const bool fonts_error = !FILESYSTEM_doesFontsDirExist();
        const bool lang_error = !FILESYSTEM_doesLangDirExist();

        if (fonts_error && lang_error)
        {
            left_msg = "[No fonts&lang folders]";
        }
        else if (fonts_error)
        {
            left_msg = "[No fonts folder]";
        }
        else if (lang_error)
        {
            left_msg = "[No lang folder]";
        }
        else if (music.mmmmmm)
        {
            left_msg = loc::gettext(STR_ID("[MMMMMM Mod Installed]", STR_M6_INSTALLED));
        }

        if (left_msg != NULL)
        {
            font::print(0, 10, 230, left_msg, tr/2, tg/2, tb/2);
        }
        break;
    }
    case Menu::levellist:
    {
        if (cl.ListOfMetaData.size()==0)
        {
            font::print_wrap(PR_CEN, -1, 90, loc::gettext(STR_ID("ERROR: No levels found.", STR_ERR_NO_LEVELS)), tr, tg, tb);
        }
        int tmp=game.currentmenuoption+(game.levelpage*8);
        if (INBOUNDS_VEC(tmp, cl.ListOfMetaData))
        {
            const bool nextlastoptions = cl.ListOfMetaData.size() > 8;
            //Don't show next/previous page or return to menu options here!
            if (nextlastoptions && game.menuoptions.size() - game.currentmenuoption<=3)
            {

            }
            else
            {
                uint32_t level_flags = PR_FONT_IDX(
                    cl.ListOfMetaData[tmp].level_main_font_idx,
                    cl.ListOfMetaData[tmp].rtl
                );
                uint32_t title_flags = cl.ListOfMetaData[tmp].title_is_gettext ? PR_FONT_INTERFACE : level_flags;
                uint32_t creator_flags = cl.ListOfMetaData[tmp].creator_is_gettext ? PR_FONT_INTERFACE : level_flags;
                const char* title = cl.ListOfMetaData[tmp].title.c_str();
                if (cl.ListOfMetaData[tmp].title_is_gettext)
                {
                    title = loc::gettext(STR_ID(title, STR_UNTITLED_LEVEL));
                }
                const char* creator = cl.ListOfMetaData[tmp].creator.c_str();
                if (cl.ListOfMetaData[tmp].creator_is_gettext)
                {
                    creator = loc::gettext(STR_ID(creator, STR_UNKNOWN_AUTHOR));
                }

                font::print(title_flags | PR_2X | PR_CEN, -1, 15, title, tr, tg, tb);
                int sp = SDL_max(10, font::height(level_flags));
                graphics.print_level_creator(creator_flags, 40, creator, tr, tg, tb);
                font::print(level_flags | PR_CEN, -1, 40+sp, cl.ListOfMetaData[tmp].website, tr, tg, tb);
                font::print(level_flags | PR_CEN, -1, 40+sp*3, cl.ListOfMetaData[tmp].Desc1, tr, tg, tb);
                font::print(level_flags | PR_CEN, -1, 40+sp*4, cl.ListOfMetaData[tmp].Desc2, tr, tg, tb);
                if (sp <= 10)
                {
                    font::print(level_flags | PR_CEN, -1, 40+sp*5, cl.ListOfMetaData[tmp].Desc3, tr, tg, tb);
                }
            }
        }
        break;
    }
    case Menu::errornostart:
        font::print_wrap(PR_CEN, -1, 65, loc::gettext(STR_ID("ERROR: This level has no start point!", STR_ERR_NO_START_POINT)), tr, tg, tb);
        break;
    case Menu::gameplayoptions:
    {
        int gameplayoptionsoffset = 0;
#if !defined(MAKEANDPLAY)
        if (game.ingame_titlemode && game.unlock[Unlock_FLIPMODE])
#endif
        {
            gameplayoptionsoffset = 1;
            if (game.currentmenuoption == 0) {
                font::print(PR_2X | PR_CEN, -1, 30, loc::gettext(STR_ID("Flip Mode", STR_FLIP_MODE_TITLE)), tr, tg, tb);
                int next_y = font::print_wrap(PR_CEN, -1, 65, loc::gettext(STR_ID("Flip the entire game vertically.", STR_FLIP_MODE_DESC)), tr, tg, tb);
                if (graphics.setflipmode)
                {
                    font::print_wrap(PR_CEN, -1, next_y, loc::gettext(STR_ID("Currently ENABLED!", STR_CURRENTLY_ENABLED)), tr, tg, tb);
                }
                else
                {
                    font::print_wrap(PR_CEN, -1, next_y, loc::gettext(STR_ID("Currently Disabled.", STR_CURRENTLY_DISABLED)), tr/2, tg/2, tb/2);
                }
            }
        }

        if (game.currentmenuoption == gameplayoptionsoffset + 0)
        {
            //Toggle FPS
            font::print(PR_2X | PR_CEN, -1, 30, loc::gettext(STR_ID("Toggle 30+ FPS", STR_TOGGLE_FPS_TITLE)), tr, tg, tb);
            int next_y = font::print_wrap(PR_CEN, -1, 65, loc::gettext(STR_ID("Change whether the game runs at 30 or over 30 FPS.", STR_TOGGLE_FPS_DESC)), tr, tg, tb);

            if (!game.over30mode)
            {
                font::print_wrap(PR_CEN, -1, next_y, loc::gettext(STR_ID("Current mode: 30 FPS", STR_AT_30_FPS)), tr/2, tg/2, tb/2);
            }
            else
            {
                font::print_wrap(PR_CEN, -1, next_y, loc::gettext(STR_ID("Current mode: Over 30 FPS", STR_OVER_30_FPS)), tr, tg, tb);
            }
            break;
        }
        else if (game.currentmenuoption == gameplayoptionsoffset + 1)
        {
            //Speedrunner options
            font::print(PR_2X | PR_CEN, -1, 30, loc::gettext(STR_ID("Speedrunner Options", STR_SPEEDRUN_OPTS_TITLE)), tr, tg, tb);
            font::print_wrap(PR_CEN, -1, 65, loc::gettext(STR_ID("Access some advanced settings that might be of interest to speedrunners.", STR_SPEEDRUN_OPTS_DESC)), tr, tg, tb);
        }
        else if (game.currentmenuoption == gameplayoptionsoffset + 2)
        {
            //Advanced options
            font::print(PR_2X | PR_CEN, -1, 30, loc::gettext(STR_ID("Advanced Options", STR_ADVANCED_OPTS_TITLE)), tr, tg, tb);
            font::print_wrap(PR_CEN, -1, 65, loc::gettext(STR_ID("All other gameplay settings.", STR_ADVANCED_OPTS_DESC)), tr, tg, tb);
        }
        else if (game.currentmenuoption == gameplayoptionsoffset + 3)
        {
            //Clear Data
            font::print(PR_2X | PR_CEN, -1, 30, loc::gettext(STR_ID("Clear Data", STR_CLEAR_DATA_TITLE)), tr, tg, tb);
            font::print_wrap(PR_CEN, -1, 65, loc::gettext(STR_ID("Delete your main game save data and unlocked play modes.", STR_CLEAR_MAIN_DATA_DESC)), tr, tg, tb);
        }
        else if (game.currentmenuoption == gameplayoptionsoffset + 4)
        {
            font::print(PR_2X | PR_CEN, -1, 30, loc::gettext(STR_ID("Clear Data", STR_CLEAR_DATA_TITLE)), tr, tg, tb);
            font::print_wrap(PR_CEN, -1, 65, loc::gettext(STR_ID("Delete your custom level save data and completion stars.", STR_CLEAR_CUSTOM_DATA_DESC)), tr, tg, tb);
        }

        break;
    }
    case Menu::options:
        switch (game.currentmenuoption)
        {
        case 0:
            font::print(PR_2X | PR_CEN, -1, 30, loc::gettext(STR_ID("Gameplay Options", STR_GAMEPLAY_TITLE)), tr, tg, tb);
            font::print_wrap(PR_CEN, -1, 65, loc::gettext(STR_ID("Adjust various gameplay settings.", STR_GAMEPLAY_DESC)), tr, tg, tb);
            break;
        case 1:
            font::print(PR_2X | PR_CEN, -1, 30, loc::gettext(STR_ID("Graphics Options", STR_GRAPHICS_TITLE)), tr, tg, tb);
            font::print_wrap(PR_CEN, -1, 65, loc::gettext(STR_ID("Adjust screen settings.", STR_GRAPHICS_DESC)), tr, tg, tb);
            break;
        case 2:
            font::print(PR_2X | PR_CEN, -1, 30, loc::gettext(STR_ID("Audio Options", STR_AUDIO_TITLE)), tr, tg, tb);
            if (music.mmmmmm)
            {
                font::print_wrap(PR_CEN, -1, 65, loc::gettext(STR_ID("Adjust volume settings and soundtrack.", STR_AUDIO_DESC_M6)), tr, tg, tb);
            }
            else
            {
                font::print_wrap(PR_CEN, -1, 65, loc::gettext(STR_ID("Adjust volume settings.", STR_AUDIO_DESC)), tr, tg, tb);
            }
            break;
        case 3:
            font::print(PR_2X | PR_CEN, -1, 30, loc::gettext(STR_ID("Game Pad Options", STR_GAME_PAD_OPTS_TITLE)), tr, tg, tb);
            font::print_wrap(PR_CEN, -1, 65, loc::gettext(STR_ID("Rebind your controller's buttons and adjust sensitivity.", STR_GAME_PAD_OPTS_DESC)), tr, tg, tb);
            break;
        case 4:
            font::print(PR_2X | PR_CEN, -1, 30, loc::gettext(STR_ID("Accessibility", STR_ACCESSIBILITY_TITLE)), tr, tg, tb);
            font::print_wrap(PR_CEN, -1, 65, loc::gettext(STR_ID("Disable screen effects, enable slowdown modes or invincibility.", STR_ACCESSIBILITY_DESC)), tr, tg, tb);
            break;
        case 5:
            font::print(PR_2X | PR_CEN,  -1, 30, loc::gettext(STR_ID("Language", STR_LANGUAGE_TITLE)), tr, tg, tb);
            font::print_wrap(PR_CEN, -1, 65, loc::gettext(STR_ID("Change the language.", STR_LANGUAGE_DESC)), tr, tg, tb);
        }
        break;
    case Menu::graphicoptions:
    {
        int offset = 0;
        if (game.currentmenuoption == offset + 0 && !gameScreen.isForcedFullscreen())
        {
            font::print(PR_2X | PR_CEN,  -1, 30, loc::gettext(STR_ID("Toggle Fullscreen", STR_FULLSCREEN_TITLE)), tr, tg, tb);
            int next_y = font::print_wrap(PR_CEN, -1, 65, loc::gettext(STR_ID("Change to fullscreen/windowed mode.", STR_FULLSCREEN_DESC)), tr, tg, tb);

            if (gameScreen.isWindowed)
            {
                font::print_wrap(PR_CEN, -1, next_y, loc::gettext(STR_ID("Current mode: WINDOWED", STR_MODE_WINDOWED)), tr, tg, tb);
            }
            else
            {
                font::print_wrap(PR_CEN, -1, next_y, loc::gettext(STR_ID("Current mode: FULLSCREEN", STR_MODE_FULLSCREEN)), tr, tg, tb);
            }
        }

        if (gameScreen.isForcedFullscreen())
        {
            --offset;
        }

        if (game.currentmenuoption == offset + 1)
        {
            font::print(PR_2X | PR_CEN,  -1, 30, loc::gettext(STR_ID("Scaling Mode", STR_SCALING_MODE_TITLE)), tr, tg, tb);
            int next_y = font::print_wrap(PR_CEN, -1, 65, loc::gettext(STR_ID("Choose letterbox/stretch/integer mode.", STR_SCALING_MODE_DESC)), tr, tg, tb);

            switch (gameScreen.scalingMode)
            {
            case SCALING_INTEGER:
                font::print_wrap(PR_CEN, -1, next_y, loc::gettext(STR_ID("Current mode: INTEGER", STR_MODE_INTEGER)), tr, tg, tb);
                break;
            case SCALING_STRETCH:
                font::print_wrap(PR_CEN, -1, next_y, loc::gettext(STR_ID("Current mode: STRETCH", STR_MODE_STRETCH)), tr, tg, tb);
                break;
            case SCALING_LETTERBOX:
            default:
                font::print_wrap(PR_CEN, -1, next_y, loc::gettext(STR_ID("Current mode: LETTERBOX", STR_MODE_LETTERBOX)), tr, tg, tb);
                break;
            }
        }
        if (game.currentmenuoption == offset + 2 && !gameScreen.isForcedFullscreen())
        {
            font::print(PR_2X | PR_CEN, -1, 30, loc::gettext(STR_ID("Resize to Nearest", STR_RESIZE_TITLE)), tr, tg, tb);
            int next_y = font::print_wrap(PR_CEN, -1, 65, loc::gettext(STR_ID("Resize to the nearest window size that is of an integer multiple.", STR_RESIZE_DESC)), tr, tg, tb);
            if (!gameScreen.isWindowed)
            {
                font::print_wrap(PR_CEN, -1, next_y, loc::gettext(STR_ID("You must be in windowed mode to use this option.", STR_YOU_MUST_BE_WINDOWED)), tr, tg, tb);
            }
        }
        if (gameScreen.isForcedFullscreen())
        {
            --offset;
        }
        if (game.currentmenuoption == offset + 3)
        {
            font::print(PR_2X | PR_CEN,  -1, 30, loc::gettext(STR_ID("Toggle Filter", STR_FILTER_TITLE)), tr, tg, tb);
            int next_y = font::print_wrap(PR_CEN, -1, 65, loc::gettext(STR_ID("Change to nearest/linear filter.", STR_FILTER_DESC)), tr, tg, tb);

            if (gameScreen.isFiltered)
            {
                font::print_wrap(PR_CEN, -1, next_y, loc::gettext(STR_ID("Current mode: LINEAR", STR_MODE_LINEAR)), tr, tg, tb);
            }
            else
            {
                font::print_wrap(PR_CEN, -1, next_y, loc::gettext(STR_ID("Current mode: NEAREST", STR_MODE_NEAREST)), tr, tg, tb);
            }
        }

        if (game.currentmenuoption == offset + 4)
        {
            font::print(PR_2X | PR_CEN,  -1, 30, loc::gettext(STR_ID("Analogue Mode", STR_ANALOGUE_TITLE)), tr, tg, tb);
            font::print_wrap(PR_CEN, -1, 65, loc::gettext(STR_ID("There is nothing wrong with your television set. Do not attempt to adjust the picture.", STR_ANALOGUE_DESC)), tr, tg, tb);
        }
        if (game.currentmenuoption == offset + 5)
        {
            font::print(PR_2X | PR_CEN, -1, 30, loc::gettext(STR_ID("Toggle VSync", STR_VSYNC_TITLE)), tr, tg, tb);
            int next_y = font::print_wrap(PR_CEN, -1, 65, loc::gettext(STR_ID("Turn VSync on or off.", STR_VSYNC_DESC)), tr, tg, tb);

            if (!gameScreen.vsync)
            {
                font::print_wrap(PR_CEN, -1, next_y, loc::gettext(STR_ID("Current mode: VSYNC OFF", STR_VSYNC_OFF)), tr/2, tg/2, tb/2);
            }
            else
            {
                font::print_wrap(PR_CEN, -1, next_y, loc::gettext(STR_ID("Current mode: VSYNC ON", STR_VSYNC_ON)), tr, tg, tb);
            }
        }
        break;
    }
    case Menu::audiooptions:
        switch (game.currentmenuoption)
        {
        case 0:
            font::print(PR_2X | PR_CEN, -1, 30, loc::gettext(STR_ID("Music Volume", STR_MUSIC_VOLUME_TITLE)), tr, tg, tb);
            font::print_wrap(PR_CEN, -1, 65, loc::gettext(STR_ID("Change the volume of the music.", STR_MUSIC_VOLUME_DESC)), tr, tg, tb);
            volumesliderrender();
            break;
        case 1:
            font::print(PR_2X | PR_CEN, -1, 30, loc::gettext(STR_ID("Sound Volume", STR_SOUND_VOLUME_TITLE)), tr, tg, tb);
            font::print_wrap(PR_CEN, -1, 65, loc::gettext(STR_ID("Change the volume of sound effects.", STR_SOUND_VOLUME_DESC)), tr, tg, tb);
            volumesliderrender();
            break;
        case 2:
        {
            if (!music.mmmmmm)
            {
                break;
            }

            font::print(PR_2X | PR_CEN, -1, 30, loc::gettext(STR_ID("Soundtrack", STR_SOUNDTRACK_TITLE)), tr, tg, tb);
            int next_y = font::print_wrap(PR_CEN, -1, 65, loc::gettext(STR_ID("Toggle between MMMMMM and PPPPPP.", STR_SOUNDTRACK_DESC)), tr, tg, tb);

            const char* soundtrack;
            if (music.usingmmmmmm)
            {
                soundtrack = loc::gettext(STR_ID("Current soundtrack: MMMMMM", STR_SOUNDTRACK_M6));
            }
            else
            {
                soundtrack = loc::gettext(STR_ID("Current soundtrack: PPPPPP", STR_SOUNDTRACK_P6));
            }
            font::print_wrap(PR_CEN, -1, next_y, soundtrack, tr, tg, tb);
            break;
        }

        }
        break;
    case Menu::credits:
        font::print(PR_CEN, -1, 50, loc::gettext(STR_ID("VVVVVV is a game by", STR_V6_IS_BY)), tr, tg, tb);
        font::print(PR_2X | PR_CEN | PR_FONT_8X8, -1, 65, "Terry Cavanagh", tr, tg, tb);

        graphics.drawimagecol(IMAGE_SITE, -1, 86, graphics.getRGB(tr, tg, tb), true);

        font::print(PR_CEN, -1, 120, loc::gettext(STR_ID("and features music by", STR_FEATURES_MUSIC_BY)), tr, tg, tb);
        font::print(PR_2X | PR_CEN | PR_FONT_8X8, -1, 135, "Magnus Pålsson", tr, tg, tb);
        graphics.drawimagecol(IMAGE_SITE2, -1, 156, graphics.getRGB(tr, tg, tb), true);
        break;
    case Menu::credits2:
        font::print(PR_CEN, -1, 40, loc::gettext(STR_ID("Roomnames are by", STR_ROOMNAMES_BY)), tr, tg, tb);
        font::print(PR_2X | PR_CEN | PR_FONT_8X8, -1, 55, "Bennett Foddy", tr, tg, tb);
        graphics.drawimagecol(IMAGE_SITE3, -1, 76, graphics.getRGB(tr, tg, tb), true);
        font::print(PR_CEN, -1, 100, loc::gettext(STR_ID("C++ version by", STR_CPP_VERSION_BY)), tr, tg, tb);
        font::print(PR_2X | PR_CEN | PR_FONT_8X8, -1, 115, "Simon Roth", tr, tg, tb);
        font::print(PR_2X | PR_CEN | PR_FONT_8X8, -1, 135, "Ethan Lee", tr, tg, tb);
        font::print(PR_2X | PR_CEN | PR_FONT_8X8, -1, 155, "Misa Kai", tr, tg, tb);
        break;
    case Menu::credits25:
        font::print(PR_CEN, -1, 40, loc::gettext(STR_ID("Beta Testing by", STR_BETA_TESTED_BY)), tr, tg, tb);
        font::print(PR_2X | PR_CEN | PR_FONT_8X8, -1, 55, "Sam Kaplan", tr, tg, tb);
        font::print(PR_2X | PR_CEN | PR_FONT_8X8, -1, 75, "Pauli Kohberger", tr, tg, tb);
        font::print(PR_CEN, -1, 130, loc::gettext(STR_ID("Ending Picture by", STR_END_PICTURE_BY)), tr, tg, tb);
        font::print(PR_2X | PR_CEN | PR_FONT_8X8, -1, 145, "Pauli Kohberger", tr, tg, tb);
        break;
    case Menu::credits_localisations_implementation:
        font::print(PR_CEN, -1, 30, loc::gettext(STR_ID("Localisation Project Led by", STR_LOCALIZED_LED_BY)), tr, tg, tb);
        font::print(PR_2X | PR_CEN | PR_FONT_8X8, -1, 45, "Dav999", tr, tg, tb);
        font::print(PR_CEN, -1, 75, loc::gettext(STR_ID("Pan-European Font Design by", STR_PE_FONT_BY)), tr, tg, tb);
        font::print(PR_2X | PR_CEN | PR_FONT_8X8, -1, 90, "Reese Rivers", tr, tg, tb);
        font::print_wrap(PR_CEN, -1, 125, loc::gettext(STR_ID("With contributions on GitHub from", STR_WITH_CONTRIB_FROM)), tr, tg, tb);
        font::print(PR_2X | PR_CEN | PR_FONT_8X8, -1, 140, "Alexandra Fox", tr, tg, tb);
        font::print(PR_2X | PR_CEN | PR_FONT_8X8, -1, 160, "mothbeanie", tr, tg, tb);
        break;
    case Menu::credits_localisations_translations:
    {
        font::print_wrap(PR_2X | PR_CEN, -1, 15, loc::gettext(STR_ID("Translators", STR_TRANSLATORS)), tr, tg, tb);

        int startidx = game.current_credits_list_index;
        int endidx = game.current_credits_list_index;
        endidx += Credits::translator_pagesize[game.translator_credits_pagenum];
        endidx = SDL_min(endidx, (int)SDL_arraysize(Credits::translators));

        int maxheight = 110;

        int totalheight = (endidx - startidx) * 10;
        int emptyspace = maxheight - totalheight;

        int yofs = 50 + (emptyspace / 2);

        for (int i = startidx; i < endidx; ++i)
        {
            if (Credits::translators[i][0] == '>')
            {
                yofs += 2;
                font::print(PR_CJK_HIGH, 88, yofs, loc::gettext(STR_ID(&Credits::translators[i][1], Credits::translators[i][1] == 'E' ? STR_EDITING_LQA : STR_TRANSLATORS)), tr, tg, tb);
            } 
            else if (Credits::translators[i][0] != ' ')
            {
                yofs += 5;
                font::print(PR_CJK_HIGH, 80, yofs, loc::gettext(STR_ID(Credits::translators[i], lang_to_id(Credits::translators[i]))), tr, tg, tb);
            }
            else
            {
                font::print(PR_FONT_8X8, 80, yofs, Credits::translators[i], tr, tg, tb);
            }
            yofs += 10;
        }
        break;
    }
    case Menu::credits3:
    {
        font::print_wrap(PR_CEN, -1, 20, loc::gettext(STR_ID("VVVVVV is supported by the following patrons", STR_V6_SUPPORTED_BY_PATRONS)), tr, tg, tb);

        int startidx = game.current_credits_list_index;
        int endidx = SDL_min(startidx + 9, (int)SDL_arraysize(Credits::superpatrons));

        int xofs = 80 - 16;
        int yofs = 40 + 20;

        for (int i = startidx; i < endidx; ++i)
        {
            font::print(PR_FONT_8X8, xofs, yofs, Credits::superpatrons[i], tr, tg, tb);
            xofs += 4;
            yofs += 14;
        }
        break;
    }
    case Menu::credits4:
    {
        font::print_wrap(PR_CEN, -1, 20, loc::gettext(STR_ID("and also by", STR_AND_ALSO_BY)), tr, tg, tb);

        int startidx = game.current_credits_list_index;
        int endidx = SDL_min(startidx + 14, (int)SDL_arraysize(Credits::patrons));

        int maxheight = 10 * 14;
        int totalheight = (endidx - startidx) * 10;
        int emptyspace = maxheight - totalheight;

        int yofs = 40 + (emptyspace / 2);

        for (int i = startidx; i < endidx; ++i)
        {
            font::print(PR_FONT_8X8, 80, yofs, Credits::patrons[i], tr, tg, tb);
            yofs += 10;
        }
        break;
    }
    case Menu::credits5:
    {
        font::print_wrap(PR_CEN, -1, 20, loc::gettext(STR_ID("With contributions on GitHub from", STR_WITH_CONTRIB_FROM)), tr, tg, tb);

        int startidx = game.current_credits_list_index;
        int endidx = SDL_min(startidx + 9, (int)SDL_arraysize(Credits::githubfriends));

        int maxheight = 14 * 9;
        int totalheight = (endidx - startidx) * 14;
        int emptyspace = maxheight - totalheight;

        int xofs, yofs;

        xofs = 80 - 16;
        yofs = 40 + 20 + (emptyspace / 2);

        for (int i = startidx; i < endidx; ++i)
        {
            font::print(PR_FONT_8X8, xofs, yofs, Credits::githubfriends[i], tr, tg, tb);
            xofs += 4;
            yofs += 14;
        }
        break;
    }
    case Menu::credits6:
        font::print_wrap(PR_CEN, -1, 20, loc::gettext(STR_ID("and thanks also to:", STR_ALSO_THANKS_TO)), tr, tg, tb);

        font::print(PR_2X | PR_CEN, -1, 60, loc::gettext(STR_ID("You!", STR_YOU)), tr, tg, tb);

        font::print_wrap(PR_CEN, -1, 100, loc::gettext(STR_ID("Your support makes it possible for me to continue making the games I want to make, now and into the future.", STR_THANKS_TO_YOUR_SUPPORT)), tr, tg, tb);

        font::print_wrap(PR_CEN, -1, 150,loc::gettext(STR_ID("Thank you!", STR_THANK_YOU)), tr, tg, tb);
        break;
    case Menu::setinvincibility:
        font::print_wrap(PR_CEN, -1, 100, loc::gettext(STR_ID("Are you sure you want to enable invincibility?", STR_WANNA_ENABLE_INVINCIBILITY)), tr, tg, tb);
        break;
    case Menu::setslowdown:
    {
        font::print(PR_2X | PR_CEN, -1, 30, loc::gettext(STR_ID("Game Speed", STR_GAME_SPEED_TITLE)), tr, tg, tb);
        int next_y = font::print_wrap(PR_CEN, -1, 65, loc::gettext(STR_ID("Select a new game speed below.", STR_GAME_SPEED_DESC)), tr, tg, tb);
        drawslowdowntext(next_y);
        break;
    }
    case Menu::newgamewarning:
        font::print_wrap(PR_CEN, -1, 100, loc::gettext(STR_ID("Are you sure? This will delete your current saves...", STR_WARNING_NEW_GAME)), tr, tg, tb);
        break;
    case Menu::cleardatamenu:
    case Menu::clearcustomdatamenu:
        font::print_wrap(PR_CEN, -1, 100, loc::gettext(STR_ID("Are you sure you want to delete all your saved data?", STR_WANNA_DELETE_DATA)), tr, tg, tb);
        break;
    case Menu::deletequicklevel:
        font::print_wrap(PR_CEN, -1, 100, loc::gettext(STR_ID("Are you sure you want to delete your quicksave?", STR_WANNA_DELETE_QUICKSAVE)), tr, tg, tb);
        break;
    case Menu::startnodeathmode:
    {
        int next_y;
        next_y = font::print_wrap(PR_CEN, -1, 45, loc::gettext(STR_ID("Good luck!", STR_GOOD_LUCK)), tr, tg, tb);
        next_y = font::print_wrap(PR_CEN, -1, next_y+15, loc::gettext(STR_ID("You cannot save in this mode.", STR_CANT_SAVE_MODE)), tr, tg, tb);
        font::print_wrap(PR_CEN, -1, next_y+5, loc::gettext(STR_ID("Would you like to disable the cutscenes during the game?", STR_WANNA_DISABLE_CUTSCENES)), tr, tg, tb);
        break;
    }
    case Menu::controller:
    {
        font::print(PR_2X | PR_CEN, -1, 30, loc::gettext(STR_ID("Game Pad", STR_GAME_PAD_TITLE)), tr, tg, tb);
        font::print_wrap(PR_CEN, -1, 55, loc::gettext(STR_ID("Change controller options.", STR_GAME_PAD_DESC)), tr, tg, tb);

        int spacing = font::height(0);
        spacing = SDL_max(spacing, 10);

        switch (game.currentmenuoption)
        {
        case 0:
        {
            font::print(PR_RTL_XFLIP, 32, 75, loc::gettext(STR_ID("Low", STR_LOW)), tr, tg, tb);
            font::print(PR_CEN, -1, 75, loc::gettext(STR_ID("Medium", STR_MEDIUM)), tr, tg, tb);
            font::print(PR_RIGHT | PR_RTL_XFLIP, 288, 75, loc::gettext(STR_ID("High", STR_HIGH)), tr, tg, tb);
            char slider[SCREEN_WIDTH_CHARS + 1];
            slider_get(slider, sizeof(slider), key.sensitivity, 5, 240);
            font::print(PR_CEN, -1, 75+spacing, slider, tr, tg, tb);
            break;
        }
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        {
            char buffer_a[SCREEN_WIDTH_CHARS + 1];
            char buffer_b[SCREEN_WIDTH_CHARS + 1];

            SDL_snprintf(buffer_a, sizeof(buffer_a), "%s%s",
                loc::gettext(STR_ID("Flip is bound to: ", STR_BOUND_FLIP)),
                BUTTONGLYPHS_get_all_gamepad_buttons(buffer_b, sizeof(buffer_b), ActionSet_InGame, Action_InGame_ACTION)
            );
            font::print(PR_CEN, -1, 75, buffer_a, tr, tg, tb);

            SDL_snprintf(buffer_a, sizeof(buffer_a), "%s%s",
                loc::gettext(STR_ID("Enter is bound to: ", STR_BOUND_ENTER)),
                BUTTONGLYPHS_get_all_gamepad_buttons(buffer_b, sizeof(buffer_b), ActionSet_InGame, Action_InGame_Map)
            );
            font::print(PR_CEN, -1, 75+spacing, buffer_a, tr, tg, tb);

            SDL_snprintf(buffer_a, sizeof(buffer_a), "%s%s",
                loc::gettext(STR_ID("Menu is bound to: ", STR_BOUND_MENU)),
                BUTTONGLYPHS_get_all_gamepad_buttons(buffer_b, sizeof(buffer_b), ActionSet_InGame, Action_InGame_Esc)
            );
            font::print(PR_CEN, -1, 75+spacing*2, buffer_a, tr, tg, tb);

            SDL_snprintf(buffer_a, sizeof(buffer_a), "%s%s",
                loc::gettext(STR_ID("Restart is bound to: ", STR_BOUND_RESTART)),
                BUTTONGLYPHS_get_all_gamepad_buttons(buffer_b, sizeof(buffer_b), ActionSet_InGame, Action_InGame_Restart)
            );
            font::print(PR_CEN, -1, 75+spacing*3, buffer_a, tr, tg, tb);

            SDL_snprintf(buffer_a, sizeof(buffer_a), "%s%s",
                loc::gettext(STR_ID("Interact is bound to: ", STR_BOUND_INTERACT)),
                BUTTONGLYPHS_get_all_gamepad_buttons(buffer_b, sizeof(buffer_b), ActionSet_InGame, Action_InGame_Interact)
            );
            font::print(PR_CEN | PR_BRIGHTNESS(game.separate_interact ? 255 : 128), -1, 75+spacing*4, buffer_a, tr, tg, tb);
            break;
        }
        }


        break;
    }
    case Menu::language:
        if (loc::languagelist.empty())
        {
            font::print_wrap(PR_CEN, -1, 90, loc::gettext(STR_ID("ERROR: No language files found.", STR_ERR_NO_LANG_FILES)), tr, tg, tb);
        }
        else if ((unsigned)game.currentmenuoption < loc::languagelist.size())
        {
            font::print_wrap(PR_CEN, -1, 8, loc::languagelist[game.currentmenuoption].credit.c_str(), tr/2, tg/2, tb/2);
            const char* select_hint;
            char buffer[SCREEN_WIDTH_CHARS + 1];
            if (BUTTONGLYPHS_keyboard_is_active())
            {
                select_hint = loc::languagelist[game.currentmenuoption].action_hint.c_str();
            }
            else
            {
                vformat_buf(buffer, sizeof(buffer),
                    loc::languagelist[game.currentmenuoption].gamepad_hint.c_str(),
                    "button:but",
                    vformat_button(ActionSet_Menu, Action_Menu_Accept)
                );
                select_hint = buffer;
            }
            font::print(PR_CEN, -1, 230, select_hint, tr/2, tg/2, tb/2);
        }
        break;
    case Menu::translator_main:
        switch (game.currentmenuoption)
        {
        case 0:
            font::print(PR_2X | PR_CEN, -1, 30, loc::gettext(STR_ID("Translator options", STR_TRANSLATOR_OPTS_DESC)), tr, tg, tb);
            font::print_wrap(PR_CEN, -1, 65, loc::gettext(STR_ID("Some options that are useful for translators and developers.", STR_TRANSLATOR_OPTS_DESC)), tr, tg, tb);
            break;
        case 1:
            font::print(PR_2X | PR_CEN, -1, 30, loc::gettext(STR_ID("Maintenance", STR_MAINTENANCE_TITLE)), tr, tg, tb);
            font::print_wrap(PR_CEN, -1, 65, loc::gettext(STR_ID("Sync all language files after adding new strings.", STR_MAINTENANCE_DESC)), tr, tg, tb);
            break;
        }
        {
            if (FILESYSTEM_isMainLangDirFromRepo())
            {
                // Just giving people who manually compiled the game some hint as to why this menu is here!
                font::print(0, 8, 208, loc::gettext(STR_ID("Repository language folder:", STR_REPO_LANG_FOLDER)), tr/2, tg/2, tb/2);
            }
            else
            {
                font::print(0, 8, 208, loc::gettext(STR_ID("Language folder:", STR_LANG_FOLDER)), tr/2, tg/2, tb/2);
            }

            font::print(PR_RIGHT, 316, 224, FILESYSTEM_getUserMainLangDirectory(), tr/2, tg/2, tb/2);
        }
        break;
    case Menu::translator_options:
        switch (game.currentmenuoption)
        {
        case 0:
            font::print(PR_2X | PR_CEN, -1, 30, loc::gettext(STR_ID("Statistics", STR_STATS_TITLE)), tr, tg, tb);
            font::print_wrap(PR_CEN, -1, 65, loc::gettext(STR_ID("Count the amount of untranslated strings for this language.", STR_LANG_STATS_DESC)), tr, tg, tb);
            break;
        case 1:
        {
            font::print(PR_2X | PR_CEN, -1, 30, loc::gettext(STR_ID("Translate rooms", STR_TRANSLATE_ROOMS_TITLE)), tr, tg, tb);
            int next_y = font::print_wrap(PR_CEN, -1, 65, loc::gettext(STR_ID("Enable room name translation mode, so you can translate room names in context. Press I for invincibility.", STR_TRANSLATE_ROOMS_DESC)), tr, tg, tb);

            if (roomname_translator::enabled)
            {
                font::print_wrap(PR_CEN, -1, next_y, loc::gettext(STR_ID("Currently ENABLED!", STR_CURRENTLY_ENABLED)), tr, tg, tb);
            }
            else
            {
                font::print_wrap(PR_CEN, -1, next_y, loc::gettext(STR_ID("Currently Disabled.", STR_CURRENTLY_DISABLED)), tr/2, tg/2, tb/2);
            }
            break;
        }
        case 2:
            font::print(PR_2X | PR_CEN, -1, 30, loc::gettext(STR_ID("Explore game", STR_EXPLORE_GAME_TITLE)), tr, tg, tb);
            font::print_wrap(PR_CEN, -1, 65, loc::gettext(STR_ID("Explore the rooms of any level in the game, to find all room names to translate.", STR_EXPLORE_GAME_DESC)), tr, tg, tb);
            break;
        case 3:
            font::print(PR_2X | PR_CEN, -1, 30, loc::gettext(STR_ID("Menu test", STR_MENU_TEST_TITLE)), tr, tg, tb);
            font::print_wrap(PR_CEN, -1, 65, loc::gettext(STR_ID("Cycle through most menus in the game. The menus will not actually work, all options take you to the next menu instead. Press Escape to stop.", STR_MENU_TEST_DESC)), tr, tg, tb);
            break;
        case 4:
            font::print(PR_2X | PR_CEN, -1, 30, loc::gettext(STR_ID("Cutscene test", STR_CUTSCENE_TEST_TITLE)), tr, tg, tb);
            font::print_wrap(PR_CEN, -1, 65, loc::gettext(STR_ID("Display all text boxes from cutscenes.xml. Only tests the basic appearance of each individual text box.", STR_CUTSCENE_TEST_DESC)), tr, tg, tb);
            break;
        case 5:
            font::print(PR_2X | PR_CEN, -1, 30, loc::gettext(STR_ID("Limits check", STR_LIMITS_CHECK_TITLE)), tr, tg, tb);
            font::print_wrap(PR_CEN, -1, 65, loc::gettext(STR_ID("Find translations that don't fit within their defined bounds.", STR_LIMITS_CHECK_DESC)), tr, tg, tb);
            break;
        }
        break;
    case Menu::translator_options_limitscheck:
    {
        size_t of = loc::limitscheck_current_overflow;
        if (of >= loc::text_overflows.size())
        {
            int next_y;
            if (loc::text_overflows.empty())
            {
                next_y = font::print_wrap(PR_CEN, -1, 20, loc::gettext(STR_ID("No text overflows found!", STR_NO_OVERFLOWS_FOUND)), tr, tg, tb);
            }
            else
            {
                next_y = font::print_wrap(PR_CEN, -1, 20, loc::gettext(STR_ID("No text overflows left!", STR_NO_OVERFLOWS_LEFT)), tr, tg, tb);
            }

            font::print_wrap(PR_CEN, -1, next_y, loc::gettext(STR_ID("Note that this detection isn't perfect.", STR_NOTE_DETECTION)), tr, tg, tb);
        }
        else
        {
            loc::TextOverflow& overflow = loc::text_overflows[of];

            char buffer[SCREEN_WIDTH_CHARS + 1];
            vformat_buf(buffer, sizeof(buffer),
                "{page}/{total}    {max_w}*{max_h} ({max_w_px}x{max_h_px})    [{lang}]",
                "page:int, total:int, max_w:int, max_h:int, max_w_px:int, max_h_px:int, lang:str",
                (int) of+1, (int) loc::text_overflows.size(),
                overflow.max_w, overflow.max_h,
                overflow.max_w_px, overflow.max_h_px,
                overflow.lang.c_str()
            );
            font::print(PR_FONT_8X8, 10, 10, buffer, tr/2, tg/2, tb/2);

            int box_x = SDL_min(10, (320-overflow.max_w_px)/2);
            graphics.fill_rect(box_x-1, 30-1, overflow.max_w_px+2, overflow.max_h_px+2, tr/3, tg/3, tb/3);

            int wraplimit;
            if (overflow.multiline)
            {
                wraplimit = overflow.max_w_px;
            }
            else
            {
                wraplimit = 320-box_x;
            }

            if (overflow.text != NULL)
            {
                font::print_wrap(overflow.flags, box_x, 30, overflow.text, tr, tg, tb, -1, wraplimit);
            }
        }
        break;
    }
    case Menu::translator_options_stats:
    {
        font::print(0, 16, 16, loc::get_langmeta()->nativename, tr, tg, tb);

        const char* line_template = "%4d";
        char buffer[5];
        int coldiv;

        #define stat_line(y, filename, untranslated_counter) \
            SDL_snprintf(buffer, sizeof(buffer), line_template, \
                untranslated_counter \
            ); \
            coldiv = untranslated_counter > 0 ? 1 : 2; \
            font::print(PR_FONT_8X8, 16, y, filename, tr/coldiv, tg/coldiv, tb/coldiv); \
            font::print(PR_FONT_8X8, 272, y, buffer, tr/coldiv, tg/coldiv, tb/coldiv)

        stat_line(48, "strings.xml", loc::n_untranslated[loc::UNTRANSLATED_STRINGS]);
        stat_line(64, "numbers.xml", loc::n_untranslated[loc::UNTRANSLATED_NUMBERS]);
        stat_line(80, "strings_plural.xml", loc::n_untranslated[loc::UNTRANSLATED_STRINGS_PLURAL]);
        stat_line(96, "cutscenes.xml", loc::n_untranslated[loc::UNTRANSLATED_CUTSCENES]);
        stat_line(112, "roomnames.xml", loc::n_untranslated_roomnames);
        stat_line(128, "roomnames_special.xml", loc::n_untranslated[loc::UNTRANSLATED_ROOMNAMES_SPECIAL]);

        #undef stat_line

        break;
    }
    case Menu::translator_options_exploregame:
        switch (game.currentmenuoption)
        {
        case 0:
            font::print(PR_2X | PR_CEN, -1, 30, loc::gettext(STR_ID("Space Station 1", STR_SPACE_STATION_1_TITLE)), tr, tg, tb);
            break;
        case 1:
            font::print(PR_2X | PR_CEN, -1, 30, loc::gettext(STR_ID("The Laboratory", STR_THE_LABORATORY_TITLE)), tr, tg, tb);
            break;
        case 2:
            font::print(PR_2X | PR_CEN, -1, 30, loc::gettext(STR_ID("The Tower", STR_THE_TOWER_TITLE)), tr, tg, tb);
            break;
        case 3:
            font::print(PR_2X | PR_CEN, -1, 30, loc::gettext(STR_ID("Space Station 2", STR_SPACE_STATION_2_TITLE)), tr, tg, tb);
            break;
        case 4:
            font::print(PR_2X | PR_CEN, -1, 30, loc::gettext(STR_ID("The Warp Zone", STR_THE_WARP_ZONE_TITLE)), tr, tg, tb);
            break;
        case 5:
            font::print(PR_2X | PR_CEN, -1, 30, loc::gettext(STR_ID("Intermission 1", STR_INTERMISSION_1_TITLE)), tr, tg, tb);
            break;
        case 6:
            font::print(PR_2X | PR_CEN, -1, 30, loc::gettext(STR_ID("Intermission 2", STR_INTERMISSION_2_TITLE)), tr, tg, tb);
            break;
        case 7:
            font::print(PR_2X | PR_CEN, -1, 30, loc::gettext(STR_ID("The Final Level", STR_THE_FINAL_LEVEL_TITLE)), tr, tg, tb);
            break;
        }
        if (roomname_translator::enabled)
        {
            if (game.currentmenuoption >= 0 && game.currentmenuoption < 8)
            {
                int names_left = loc::n_untranslated_roomnames_area[game.currentmenuoption + 1];
                int coldiv = names_left > 0 ? 1 : 2;

                char buffer[4*SCREEN_WIDTH_CHARS + 1];
                loc::gettext_plural_fill(
                    buffer, sizeof(buffer),
                    "{n} normal room names untranslated",
                    "{n} normal room name untranslated",
                    "n:int",
                    names_left
                );
                font::print_wrap(PR_CEN, -1, 65, buffer, tr/coldiv, tg/coldiv, tb/coldiv);
            }
        }
        else
        {
            font::print_wrap(PR_CEN, -1, 65, loc::gettext(STR_ID("You have not enabled room name translation mode!", STR_NOT_ENABLED_TRANSLATOR)), tr, tg, tb);
        }
        break;
    case Menu::translator_maintenance:
        switch (game.currentmenuoption)
        {
        case 0:
            font::print(PR_2X | PR_CEN, -1, 30, loc::gettext(STR_ID("Sync language files", STR_SYNC_LANGS_TITLE)), tr, tg, tb);
            font::print_wrap(PR_CEN, -1, 65, loc::gettext(STR_ID("Merge all new strings from the template files into the translation files, keeping existing translations.", STR_SYNC_LANGS_DESC)), tr, tg, tb);
            break;
        case 1:
            font::print(PR_2X | PR_CEN, -1, 30, loc::gettext(STR_ID("Statistics", STR_STATS_TITLE)), tr, tg, tb);
            font::print_wrap(PR_CEN, -1, 65, loc::gettext(STR_ID("Count the amount of untranslated strings for each language.", STR_GLOBAL_STATS_DESC)), tr, tg, tb);
            break;
        case 2:
            font::print(PR_2X | PR_CEN, -1, 30, loc::gettext(STR_ID("Limits check", STR_LIMITS_CHECK_TITLE)), tr, tg, tb);
            font::print_wrap(PR_CEN, -1, 65, loc::gettext(STR_ID("Find translations that don't fit within their defined bounds.", STR_LIMITS_CHECK_DESC)), tr, tg, tb);
        }
        break;
    case Menu::translator_maintenance_sync:
    {
        int next_y = font::print_wrap(PR_CEN, -1, 20, loc::gettext(STR_ID("If new strings were added to the English template language files, this feature will insert them in the translation files for all languages. Make a backup, just in case.", STR_IF_NEW_STRINGS)), tr, tg, tb);

        font::print(PR_CEN, -1, next_y, loc::gettext(STR_ID("Full syncing EN→All:", STR_FULL_SYNCING)), tr, tg, tb);
        next_y = font::print_wrap(PR_CEN | PR_FONT_8X8, -1, next_y+10, "meta.xml\nstrings.xml\nstrings_plural.xml\ncutscenes.xml\nroomnames.xml\nroomnames_special.xml", tr/2, tg/2, tb/2);

        font::print(PR_CEN, -1, next_y, loc::gettext(STR_ID("Syncing not supported:", STR_SYNC_NOT_SUPPORTED)), tr, tg, tb);
        font::print_wrap(PR_CEN | PR_FONT_8X8, -1, next_y+10, "numbers.xml", tr/2, tg/2, tb/2);
        break;
    }
    case Menu::translator_error_setlangwritedir:
        font::print_wrap(PR_CEN, -1, 95, loc::gettext(STR_ID("ERROR: Could not write to language folder! Make sure there is no \"lang\" folder next to the regular saves.", STR_ERR_WRITE_LANG)), tr, tg, tb);
        break;
    case Menu::speedrunneroptions:
        switch (game.currentmenuoption)
        {
        case 0:
        {
            font::print(PR_2X | PR_CEN, -1, 30, loc::gettext(STR_ID("Glitchrunner Mode", STR_GLITCH_TITLE)), tr, tg, tb);
            int next_y = font::print_wrap(PR_CEN, -1, 65, loc::gettext(STR_ID("Re-enable glitches that existed in previous versions of the game.", STR_GLITCH_DESC)), tr, tg, tb);
            drawglitchrunnertext(next_y);
            break;
        }
        case 1:
        {
            font::print(PR_2X | PR_CEN, -1, 30, loc::gettext(STR_ID("Input Delay", STR_DELAY_TITLE)), tr, tg, tb);
            int next_y = font::print_wrap(PR_CEN, -1, 65, loc::gettext(STR_ID("Re-enable the 1-frame input delay from previous versions of the game.", STR_DELAY_DESC)), tr, tg, tb);
            if (game.inputdelay)
            {
                font::print_wrap(PR_CEN, -1, next_y, loc::gettext(STR_ID("Input delay is ON", STR_DELAY_ON)), tr, tg, tb);
            }
            else
            {
                font::print_wrap(PR_CEN, -1, next_y, loc::gettext(STR_ID("Input delay is OFF", STR_DELAY_OFF)), tr / 2, tg / 2, tb / 2);
            }
            break;
        }
        case 2:
        {
            char buffer[SCREEN_WIDTH_CHARS + 1];
            const char* button;

            font::print(PR_2X | PR_CEN, -1, 30, loc::gettext(STR_ID("Interact Button", STR_INTERACT_BUTTON_TITLE)), tr, tg, tb);
            int next_y = font::print_wrap(PR_CEN, -1, 65, loc::gettext(STR_ID("Toggle whether you interact with prompts using ENTER or E.", STR_INTERACT_BUTTON_DESC)), tr, tg, tb);

            if (game.separate_interact)
            {
                button = loc::gettext(STR_ID("E", STR_E));
            }
            else
            {
                button = loc::gettext(STR_ID("ENTER", STR_ENTER));
            }

            vformat_buf(buffer, sizeof(buffer), loc::gettext(STR_ID("Interact button: {button}", STR_INTERACT_BUTTON_SET)), "button:str", button);
            font::print_wrap(PR_CEN, -1, next_y, buffer, tr, tg, tb);
            break;
        }
        case 3:
        {
            font::print(PR_2X | PR_CEN, -1, 30, loc::gettext(STR_ID("Fake Load Screen", STR_FAKE_LOAD_TITLE)), tr, tg, tb);
            int next_y = font::print_wrap(PR_CEN, -1, 65, loc::gettext(STR_ID("Disable the fake loading screen which appears on game launch.", STR_FAKE_LOAD_DESC)), tr, tg, tb);
            if (game.skipfakeload)
                font::print_wrap(PR_CEN, -1, next_y, loc::gettext(STR_ID("Fake loading screen is OFF", STR_FAKE_LOAD_OFF)), tr / 2, tg / 2, tb / 2);
            else
                font::print_wrap(PR_CEN, -1, next_y, loc::gettext(STR_ID("Fake loading screen is ON", STR_FAKE_LOAD_ON)), tr, tg, tb);
            break;
        }
        case 4:
        {
            font::print(PR_2X | PR_CEN, -1, 30, loc::gettext(STR_ID("In-Game Timer", STR_TIMER_TITLE)), tr, tg, tb);
            int next_y = font::print_wrap(PR_CEN, -1, 65, loc::gettext(STR_ID("Toggle the in-game timer outside of time trials.", STR_TIMER_DESC)), tr, tg, tb);
            if (game.showingametimer)
            {
                font::print_wrap(PR_CEN, -1, next_y, loc::gettext(STR_ID("In-Game Timer is ON", STR_TIMER_ON)), tr, tg, tb);
            }
            else
            {
                font::print_wrap(PR_CEN, -1, next_y, loc::gettext(STR_ID("In-Game Timer is OFF", STR_TIMER_OFF)), tr / 2, tg / 2, tb / 2);
            }
            break;
        }
        case 5:
        {
            font::print(PR_2X | PR_CEN, -1, 30, loc::gettext(STR_ID("English Sprites", STR_SPRITES_TITLE)), tr, tg, tb);
            int next_y = font::print_wrap(PR_CEN, -1, 65, loc::gettext(STR_ID("Show the original English word enemies regardless of your language setting.", STR_SPRITES_DESC)), tr, tg, tb);
            if (loc::english_sprites)
            {
                font::print_wrap(PR_CEN, -1, next_y, loc::gettext(STR_ID("Sprites are currently ALWAYS ENGLISH", STR_SPRITES_ALWAYS_EN)), tr, tg, tb);
            }
            else
            {
                font::print_wrap(PR_CEN, -1, next_y, loc::gettext(STR_ID("Sprites are currently translated", STR_SPRITES_TRANSLATED)), tr / 2, tg / 2, tb / 2);
            }
            break;
        }
        }
        break;
    case Menu::setglitchrunner:
    {
        font::print(PR_2X | PR_CEN, -1, 30, loc::gettext(STR_ID("Glitchrunner Mode", STR_GLITCH_TITLE)), tr, tg, tb);
        int next_y = font::print_wrap(PR_CEN, -1, 65, loc::gettext(STR_ID("Select a new glitchrunner version below.", STR_SELECT_GLITCH)), tr, tg, tb);
        drawglitchrunnertext(next_y);
        break;
    }
    case Menu::advancedoptions:
        switch (game.currentmenuoption)
        {
        case 0:
        {
            font::print(PR_2X | PR_CEN, -1, 30, loc::gettext(STR_ID("Unfocus Pause", STR_UNFOCUS_PAUSE_TITLE)), tr, tg, tb);
            int next_y = font::print_wrap(PR_CEN, -1, 65, loc::gettext(STR_ID("Toggle if the game will pause when the window is unfocused.", STR_UNFOCUS_PAUSE_DESC)), tr, tg, tb);
            if (game.disablepause)
            {
                font::print_wrap(PR_CEN, -1, next_y, loc::gettext(STR_ID("Unfocus pause is OFF", STR_UNFOCUS_PAUSE_OFF)), tr/2, tg/2, tb/2);
            }
            else
            {
                font::print_wrap(PR_CEN, -1, next_y, loc::gettext(STR_ID("Unfocus pause is ON", STR_UNFOCUS_PAUSE_ON)), tr, tg, tb);
            }
            break;
        }
        case 1:
        {
            font::print(PR_2X | PR_CEN, -1, 30, loc::gettext(STR_ID("Unfocus Audio", STR_UNFOCUS_AUDIO_PAUSE_TITLE)), tr, tg, tb);
            int next_y = font::print_wrap(PR_CEN, -1, 65, loc::gettext(STR_ID("Toggle if the audio will pause when the window is unfocused.", STR_UNFOCUS_AUDIO_PAUSE_DESC)), tr, tg, tb);
            if (game.disableaudiopause)
            {
                font::print_wrap(PR_CEN, -1, next_y, loc::gettext(STR_ID("Unfocus audio pause is OFF", STR_UNFOCUS_AUDIO_PAUSE_OFF)), tr/2, tg/2, tb/2);
            }
            else
            {
                font::print_wrap(PR_CEN, -1, next_y, loc::gettext(STR_ID("Unfocus audio pause is ON", STR_UNFOCUS_AUDIO_PAUSE_ON)), tr, tg, tb);
            }
            break;
        }
        case 2:
            font::print(PR_2X | PR_CEN, -1, 30, loc::gettext(STR_ID("Room Name BG", STR_RNBG_TITLE)), tr, tg, tb);
            int next_y = font::print_wrap(PR_CEN, -1, 65, loc::gettext(STR_ID("Lets you see through what is behind the name at the bottom of the screen.", STR_RNBG_DESC)), tr, tg, tb);
            if (graphics.translucentroomname)
                font::print_wrap(PR_CEN, -1, next_y, loc::gettext(STR_ID("Room name background is TRANSLUCENT", STR_RNBG_TRANSLUCENT)), tr/2, tg/2, tb/2);
            else
                font::print_wrap(PR_CEN, -1, next_y, loc::gettext(STR_ID("Room name background is OPAQUE", STR_RNBG_OPAQUE)), tr, tg, tb);
            break;
        }
        break;
    case Menu::accessibility:
    {
#ifdef MAKEANDPLAY
 #define OFFSET 0
#else
 #define OFFSET 1
#endif

        switch (game.currentmenuoption)
        {
#if !defined(MAKEANDPLAY)
        case 0:
            font::print(PR_2X | PR_CEN, -1, 30, loc::gettext(STR_ID("Unlock Play Modes", STR_UNLOCK_MODES_TITLE)), tr, tg, tb);
            font::print_wrap(PR_CEN, -1, 65, loc::gettext(STR_ID("Unlock parts of the game normally unlocked as you progress.", STR_UNLOCK_MODES_DESC)), tr, tg, tb);
            break;
#endif
        case OFFSET+0:
        {
            font::print(PR_2X | PR_CEN, -1, 30, loc::gettext(STR_ID("Invincibility", STR_INVINCIBILITY_TITLE)), tr, tg, tb);
            int next_y = font::print_wrap(PR_CEN, -1, 65, loc::gettext(STR_ID("Explore the game freely without dying. (Can cause glitches.)", STR_INVINCIBILITY_DESC)), tr, tg, tb);
            if (map.invincibility)
            {
                font::print_wrap(PR_CEN, -1, next_y, loc::gettext(STR_ID("Invincibility is ON.", STR_INVINCIBILITY_ON)), tr, tg, tb);
            }
            else
            {
                font::print_wrap(PR_CEN, -1, next_y, loc::gettext(STR_ID("Invincibility is OFF.", STR_INVINCIBILITY_OFF)), tr / 2, tg / 2, tb / 2);
            }
            break;
        }
        case OFFSET+1:
        {
            font::print(PR_2X | PR_CEN, -1, 30, loc::gettext(STR_ID("Slowdown", STR_SLOWDOWN_TITLE)), tr, tg, tb);
            int next_y = font::print_wrap(PR_CEN, -1, 65, loc::gettext(STR_ID("Reduce the game speed.", STR_SLOWDOWN_DESC)), tr, tg, tb);
            drawslowdowntext(next_y);
            break;
        }
        case OFFSET+2:
        {
            font::print(PR_2X | PR_CEN, -1, 30, loc::gettext(STR_ID("Backgrounds", STR_BACKGROUND_TITLE)), tr, tg, tb);
            int next_y = font::print_wrap(PR_CEN, -1, 65, loc::gettext(STR_ID("Disable animated backgrounds in menus and during gameplay.", STR_BACKGROUND_DESC)), tr, tg, tb);
            if (!game.colourblindmode)
            {
                font::print_wrap(PR_CEN, -1, next_y, loc::gettext(STR_ID("Backgrounds are ON.", STR_BACKGROUND_ON)), tr, tg, tb);
            }
            else
            {
                font::print_wrap(PR_CEN, -1, next_y, loc::gettext(STR_ID("Backgrounds are OFF.", STR_BACKGROUND_OFF)), tr / 2, tg / 2, tb / 2);
            }
            break;
        }
        case OFFSET+3:
        {
            font::print(PR_2X | PR_CEN, -1, 30, loc::gettext(STR_ID("Screen Effects", STR_SCREENFX_TITLE)), tr, tg, tb);
            int next_y = font::print_wrap(PR_CEN, -1, 65, loc::gettext(STR_ID("Disables screen shakes and flashes.", STR_SCREENFX_DESC)), tr, tg, tb);
            if (!game.noflashingmode)
            {
                font::print_wrap(PR_CEN, -1, next_y, loc::gettext(STR_ID("Screen Effects are ON.", STR_SCREENFX_ON)), tr, tg, tb);
            }
            else
            {
                font::print_wrap(PR_CEN, -1, next_y, loc::gettext(STR_ID("Screen Effects are OFF.", STR_SCREENFX_OFF)), tr / 2, tg / 2, tb / 2);
            }
            break;
        }
        case OFFSET+4:
        {
            const char* text;

            font::print(PR_2X | PR_CEN, -1, 30, loc::gettext(STR_ID("Text Outline", STR_TEXT_OUTLINE_TITLE)), tr, tg, tb);
            int next_y = font::print_wrap(PR_CEN, -1, 65, loc::gettext(STR_ID("Disables outline on game text.", STR_TEXT_OUTLINE_DESC)), tr, tg, tb);

            graphics.fill_rect(0, next_y-4, 320, 16, tr, tg, tb);

            if (!graphics.notextoutline)
            {
                text = loc::gettext(STR_ID("Text outlines are ON.", STR_TEXT_OUTLINE_ON));
            }
            else
            {
                text = loc::gettext(STR_ID("Text outlines are OFF.", STR_TEXT_OUTLINE_OFF));
            }

            font::print(PR_BOR | PR_CEN, -1, next_y, text, 255, 255, 255);
            break;
        }

        }
        break;

#undef OFFSET
    }
    case Menu::playint1:
    case Menu::playint2:
        font::print_wrap(PR_CEN, -1, 65, loc::gettext(STR_ID("Who do you want to play the level with?", STR_WITH_WHO)), tr, tg, tb);
        break;
    case Menu::playmodes:
        switch (game.currentmenuoption)
        {
        case 0:
        {
            font::print(PR_2X | PR_CEN, -1, 30, loc::gettext(STR_ID("Time Trials", STR_TIME_TRIALS_TITLE)), tr, tg, tb);
            int next_y = font::print_wrap(PR_CEN, -1, 65, loc::gettext(STR_ID("Replay any level in the game in a competitive time trial mode.", STR_TIME_TRIALS_DESC)), tr, tg, tb);

            if (game.nocompetitive())
            {
                font::print_wrap(PR_CEN, -1, next_y, loc::gettext(STR_ID("Time Trials are not available with slowdown or invincibility.", STR_TIME_TRIALS_ARE_LEGIT)), tr, tg, tb);
            }
            break;
        }
        case 1:
        {
            font::print(PR_2X | PR_CEN, -1, 30, loc::gettext(STR_ID("Intermissions", STR_INTERMISSIONS_TITLE)), tr, tg, tb);
            int next_y = font::print_wrap(PR_CEN, -1, 65, loc::gettext(STR_ID("Replay the intermission levels.", STR_INTERMISSIONS_DESC)), tr, tg, tb);

            if (!game.unlock[Unlock_INTERMISSION_REPLAYS])
            {
                font::print_wrap(PR_CEN, -1, next_y, loc::gettext(STR_ID("TO UNLOCK: Complete the intermission levels in-game.", STR_TO_UNLOCK_IMS)), tr, tg, tb);
            }
            break;
        }
        case 2:
        {
            font::print(PR_2X | PR_CEN, -1, 30, loc::gettext(STR_ID("No Death Mode", STR_NO_DEATH_TITLE)), tr, tg, tb);
            int next_y = font::print_wrap(PR_CEN, -1, 65, loc::gettext(STR_ID("Play the entire game without dying once.", STR_NO_DEATH_DESC)), tr, tg, tb);

            if (game.nocompetitive())
            {
                font::print_wrap(PR_CEN, -1, next_y, loc::gettext(STR_ID("No Death Mode is not available with slowdown or invincibility.", STR_NO_DEATH_IS_LEGIT)), tr, tg, tb);
            }
            else if (!game.unlock[Unlock_NODEATHMODE])
            {
                font::print_wrap(PR_CEN, -1, next_y, loc::gettext(STR_ID("TO UNLOCK: Achieve an S-rank or above in at least 4 time trials.", STR_TO_UNLOCK_NO_DEATH)), tr, tg, tb);
            }
            break;
        }
        case 3:
            // WARNING: Partially duplicated in Menu::options
            font::print(PR_2X | PR_CEN, -1, 30, loc::gettext(STR_ID("Flip Mode", STR_FLIP_MODE_TITLE)), tr, tg, tb);
            int next_y = font::print_wrap(PR_CEN, -1, 65, loc::gettext(STR_ID("Flip the entire game vertically. Compatible with other game modes.", STR_FLIP_MODE_DESC_COMPAT)), tr, tg, tb);

            if (game.unlock[Unlock_FLIPMODE])
            {
                if (graphics.setflipmode)
                {
                    font::print_wrap(PR_CEN, -1, next_y, loc::gettext(STR_ID("Currently ENABLED!", STR_CURRENTLY_ENABLED)), tr, tg, tb);
                }
                else
                {
                    font::print_wrap(PR_CEN, -1, next_y, loc::gettext(STR_ID("Currently Disabled.", STR_CURRENTLY_DISABLED)), tr/2, tg/2, tb/2);
                }
            }
            else
            {
                font::print_wrap(PR_CEN, -1, next_y, loc::gettext(STR_ID("TO UNLOCK: Complete the game.", STR_TO_UNLOCK_FLIP_MODE)), tr, tg, tb);
            }
            break;
        }
        break;
    case Menu::youwannaquit:
        font::print_wrap(PR_CEN, -1, 75, loc::gettext(STR_ID("Are you sure you want to quit?", STR_WANNA_QUIT)), tr, tg, tb);
        break;
    case Menu::continuemenu:
    {
        const char* title = NULL;
        struct Game::Summary* summary = NULL;

        switch (game.currentmenuoption)
        {
        case 0:
            title = loc::gettext(STR_ID("Tele Save", STR_TELE_SAVE_TITLE));
            summary = &game.last_telesave;
            break;
        case 1:
            title = loc::gettext(STR_ID("Quick Save", STR_QUICK_SAVE_TITLE));
            summary = &game.last_quicksave;
            break;
        }

        if (summary != NULL)
        {
            graphics.drawpixeltextbox(17, 65-20, 286, 90, 65, 185, 207);

            font::print(PR_2X | PR_CEN, -1, 20, title, tr, tg, tb);
            font::print(
                PR_CEN, -1, 80-20,
                loc::gettext_roomname_special(map.currentarea(summary->saverx, summary->savery)),
                25, 255 - (help.glow / 2), 255 - (help.glow / 2)
            );
            for (int i = 0; i < 6; i++)
            {
                graphics.drawcrewman(169-(3*42)+(i*42), 95-20, i, summary->crewstats[i], true);
            }
            font::print(
                0, 59, 132-20,
                game.giventimestring(
                    summary->hours,
                    summary->minutes,
                    summary->seconds
                ),
                255 - (help.glow / 2), 255 - (help.glow / 2), 255 - (help.glow / 2)
            );
            char buffer[SCREEN_WIDTH_CHARS + 1];
            vformat_buf(buffer, sizeof(buffer),
                loc::gettext(STR_ID("{savebox_n_trinkets|wordy}", STR_SAVEBOX_TRINKETS_WORDY)),
                "savebox_n_trinkets:int",
                summary->trinkets
            );
            font::print(PR_RIGHT, 262, 132-20, buffer, 255 - (help.glow / 2), 255 - (help.glow / 2), 255 - (help.glow / 2));

            graphics.draw_sprite(34, 126-20, 50, graphics.col_clock);
            graphics.draw_sprite(270, 126-20, 22, graphics.col_trinket);
        }
        break;
    }
    case Menu::gameover:
    case Menu::gameover2:
    {
        font::print(PR_3X | PR_CEN, -1, 25, loc::gettext(STR_ID("GAME OVER", STR_GAME_OVER)), tr, tg, tb);

        for (size_t i = 0; i < SDL_arraysize(game.ndmresultcrewstats); i++)
        {
            graphics.drawcrewman(169-(3*42)+(i*42), 68, i, game.ndmresultcrewstats[i], true);
        }
        char buffer[2*SCREEN_WIDTH_CHARS + 1];
        loc::gettext_plural_fill(
            buffer, sizeof(buffer),
            "You rescued {n_crew|wordy} crewmates",
            "You rescued {n_crew|wordy} crewmate",
            "n_crew:int",
            game.ndmresultcrewrescued
        );
        font::print(PR_CEN, -1, 100, buffer, tr, tg, tb);

        loc::gettext_plural_fill(
            buffer, sizeof(buffer),
            "and found {n_trinkets|wordy} trinkets.",
            "and found {n_trinkets|wordy} trinket.",
            "n_trinkets:int",
            game.ndmresulttrinkets
        );
        font::print_wrap(PR_CEN | PR_CJK_LOW, -1, 110, buffer, tr, tg, tb);

        font::print(PR_CEN, -1, 145, loc::gettext(STR_ID("You managed to reach:", STR_REACHED)), tr, tg, tb);
        font::print(
            PR_CEN | PR_CJK_LOW, -1, 155,
            loc::gettext_roomname(
                false,
                game.ndmresulthardestroom_x, game.ndmresulthardestroom_y,
                game.ndmresulthardestroom.c_str(), game.ndmresulthardestroom_specialname
            ),
            tr, tg, tb
        );

        const char* encouragement;
        switch (game.ndmresultcrewrescued)
        {
        case 1:
            encouragement = loc::gettext(STR_ID("Keep trying! You'll get there!", STR_KEEP_TRYING));
            break;
        case 2:
            encouragement = loc::gettext(STR_ID("Nice one!", STR_NICE_ONE));
            break;
        case 3:
            encouragement = loc::gettext(STR_ID("Wow! Congratulations!", STR_WOW_CONGRATS));
            break;
        case 4:
            encouragement = loc::gettext(STR_ID("Incredible!", STR_INCREDIBLE));
            break;
        case 5:
            encouragement = loc::gettext(STR_ID("Unbelievable! Well done!", STR_UNBELIEVABLE));
            break;
        default:
            encouragement = loc::gettext(STR_ID("Er, how did you do that?", STR_ER_HOW));
            break;
        }

        font::print_wrap(PR_CEN, -1, 190, encouragement, tr, tg, tb);
        break;
    }
    case Menu::nodeathmodecomplete:
    case Menu::nodeathmodecomplete2:
    {
        font::print(PR_4X | PR_CEN | PR_CJK_LOW, -1, 8, loc::gettext(STR_ID("WOW", STR_WOW_MEGA)), tr, tg, tb);

        for (size_t i = 0; i < SDL_arraysize(game.ndmresultcrewstats); i++)
        {
            graphics.drawcrewman(169-(3*42)+(i*42), 68, i, game.ndmresultcrewstats[i], true);
        }
        font::print(PR_CEN, -1, 100, loc::gettext(STR_ID("You rescued all the crewmates!", STR_RESCUED_ALL_CREWMATE)), tr, tg, tb);

        char buffer[3*SCREEN_WIDTH_CHARS + 1];
        loc::gettext_plural_fill(
            buffer, sizeof(buffer),
            "And you found {n_trinkets|wordy} trinkets.",
            "And you found {n_trinkets|wordy} trinket.",
            "n_trinkets:int",
            game.ndmresulttrinkets
        );
        font::print_wrap(PR_CEN | PR_CJK_LOW, -1, 110, buffer, tr, tg, tb);

        font::print_wrap(PR_CEN, -1, 160, loc::gettext(STR_ID("A new trophy has been awarded and placed in the secret lab to acknowledge your achievement!", STR_NEW_TROPHY_AWARDED)), tr, tg, tb);
        break;
    }
    case Menu::timetrialcomplete:
    case Menu::timetrialcomplete2:
    case Menu::timetrialcomplete3:
    {
        font::print(PR_3X | PR_CEN, -1, 20, loc::gettext(STR_ID("Results", STR_RESULTS)), tr, tg, tb);

        std::string tempstring = game.resulttimestring() + loc::gettext(STR_ID(" / ", STR_TIMES_DELIM)) + game.timetstring(game.timetrialresultpar) + loc::gettext(STR_ID(".99", STR_POINT_99));

        uint32_t plus1_flags = PR_RIGHT | PR_CJK_LOW | PR_RTL_XFLIP;
        int plus1_offset = 0;
        if (font::len(0, tempstring.c_str()) + font::len(0, loc::gettext(STR_ID("+1 Rank!", STR_RANK_UP))) > (292-49))
        {
            // Time and "+1 Rank!" don't fit together, so put it next to titles instead
            plus1_flags = PR_RIGHT | PR_CJK_HIGH;
            plus1_offset = -10;
        }

        /* sprite_x_1 is used for the clock and trinket,
         * sprite_x_2 is used for the player. */
        int sprite_x_1, sprite_x_2;
        if (!font::is_rtl(PR_FONT_INTERFACE))
        {
            sprite_x_1 = 22;
            sprite_x_2 = 22 - 4;
        }
        else
        {
            sprite_x_1 = SCREEN_WIDTH_PIXELS - 22 - 16;
            sprite_x_2 = SCREEN_WIDTH_PIXELS - 22 - 16 - 4;
        }

        graphics.drawspritesetcol(sprite_x_1, 80-15, 50, 22);
        font::print(PR_CJK_HIGH | PR_RTL_XFLIP, 49, 80-15, loc::gettext(STR_ID("TIME TAKEN:", STR_TIME_TAKEN)), 255, 255, 255);
        font::print(PR_CJK_LOW | PR_RTL_XFLIP, 49, 90-15, tempstring, tr, tg, tb);
        if (game.timetrialresulttime <= game.timetrialresultpar)
        {
            font::print(plus1_flags, 292, 90-15+plus1_offset, loc::gettext(STR_ID("+1 Rank!", STR_RANK_UP)), 255, 255, 255);
        }

        tempstring = help.String(game.timetrialresultdeaths);
        graphics.drawspritesetcol(sprite_x_2, 80+20-4, 12, 22);
        font::print(PR_CJK_HIGH | PR_RTL_XFLIP, 49, 80+20, loc::gettext(STR_ID("NUMBER OF DEATHS:", STR_NUM_DEATHS)), 255, 255, 255);
        font::print(PR_CJK_LOW | PR_RTL_XFLIP, 49, 90+20, tempstring, tr, tg, tb);
        if (game.timetrialresultdeaths == 0)
        {
            font::print(plus1_flags, 292, 90+20+plus1_offset, loc::gettext(STR_ID("+1 Rank!", STR_RANK_UP)), 255, 255, 255);
        }

        char buffer[SCREEN_WIDTH_CHARS + 1];
        vformat_buf(
            buffer, sizeof(buffer),
            loc::gettext(STR_ID("{n_trinkets} of {max_trinkets}", STR_TOTAL_TRINKETS_OF)),
            "n_trinkets:int, max_trinkets:int",
            game.timetrialresulttrinkets, game.timetrialresultshinytarget
        );
        graphics.drawspritesetcol(sprite_x_1, 80+55, 22, 22);
        font::print(PR_CJK_HIGH | PR_RTL_XFLIP, 49, 80+55, loc::gettext(STR_ID("SHINY TRINKETS:", STR_SHINY_TRINKETS)), 255, 255, 255);
        font::print(PR_CJK_LOW | PR_RTL_XFLIP, 49, 90+55, buffer, tr, tg, tb);
        if (game.timetrialresulttrinkets >= game.timetrialresultshinytarget)
        {
            font::print(plus1_flags, 292, 90+55+plus1_offset, loc::gettext(STR_ID("+1 Rank!", STR_RANK_UP)), 255, 255, 255);
        }

        const char* rank = "";
        switch(game.timetrialrank)
        {
        case 0:
            rank = loc::gettext(STR_ID("B", STR_B));
            break;
        case 1:
            rank = loc::gettext(STR_ID("A", STR_A));
            break;
        case 2:
            rank = loc::gettext(STR_ID("S", STR_S));
            break;
        case 3:
            rank = loc::gettext(STR_ID("V", STR_V));
            break;
        }
        int rankw = font::len(PR_4X, rank);
        int ranktextw = font::len(PR_2X, loc::gettext(STR_ID("Rank:", STR_RANK))) + 16 + rankw;
        int ranktextx = (320-ranktextw)/2;
        int rankx = ranktextx + ranktextw - rankw;
        if (game.currentmenuname == Menu::timetrialcomplete2 || game.currentmenuname == Menu::timetrialcomplete3)
        {
            font::print(PR_2X | PR_RTL_XFLIP, ranktextx, 175, loc::gettext(STR_ID("Rank:", STR_RANK)), tr, tg, tb);
        }

        if (game.currentmenuname == Menu::timetrialcomplete3)
        {
            font::print(PR_4X | PR_RTL_XFLIP, rankx, 165, rank, 255, 255, 255);
        }
        break;
    }
    case Menu::unlockmenutrials:
        font::print(PR_2X | PR_CEN, -1, 30, loc::gettext(STR_ID("Unlock Time Trials", STR_UNLOCK_TRIALS_TITLE)), tr, tg, tb);
        font::print_wrap(PR_CEN, -1, 65, loc::gettext(STR_ID("You can unlock each time trial separately.", STR_UNLOCK_TRIALS_SEPARATELY)), tr, tg, tb);
        break;
    case Menu::timetrials:
    {
        bool unlocked = false;
        int id_trial = game.currentmenuoption;
        int par;
        int max_trinkets;

        switch (game.currentmenuoption)
        {
        case 0:
            if (game.unlock[Unlock_TIMETRIAL_SPACESTATION1])
            {
                font::print(PR_2X | PR_CEN, -1, 30, loc::gettext(STR_ID("Space Station 1", STR_SPACE_STATION_1_TITLE)), tr, tg, tb);
                unlocked = true;
                par = 75;
                max_trinkets = 2;
            }
            else
            {
                font::print(PR_2X | PR_CEN, -1, 30, loc::gettext(STR_ID("???", STR_QQQ)), tr, tg, tb);
                font::print(PR_CEN, -1, 60, loc::gettext(STR_ID("TO UNLOCK:", STR_TO_UNLOCK)), tr, tg, tb);
                font::print(PR_CEN, -1, 75, loc::gettext(STR_ID("Rescue Violet", STR_RESCUE_VIOLET)), tr, tg, tb);
                font::print(PR_CEN, -1, 87, loc::gettext(STR_ID("Find three trinkets", STR_FIND_3_TRINKETS)), tr, tg, tb);
            }
            break;
        case 1:
            if (game.unlock[Unlock_TIMETRIAL_LABORATORY])
            {
                font::print(PR_2X | PR_CEN, -1, 30, loc::gettext(STR_ID("The Laboratory", STR_THE_LABORATORY_TITLE)), tr, tg, tb);
                unlocked = true;
                par = 165;
                max_trinkets = 4;
            }
            else
            {
                font::print(PR_2X | PR_CEN, -1, 30, loc::gettext(STR_ID("???", STR_QQQ)), tr, tg, tb);
                font::print(PR_CEN, -1, 60, loc::gettext(STR_ID("TO UNLOCK:", STR_TO_UNLOCK)), tr, tg, tb);
                font::print(PR_CEN, -1, 75, loc::gettext(STR_ID("Rescue Victoria", STR_RESCUE_VICTORIA)), tr, tg, tb);
                font::print(PR_CEN, -1, 87, loc::gettext(STR_ID("Find six trinkets", STR_FIND_6_TRINKETS)), tr, tg, tb);
            }
            break;
        case 2:
            if (game.unlock[Unlock_TIMETRIAL_TOWER])
            {
                font::print(PR_2X | PR_CEN, -1, 30, loc::gettext(STR_ID("The Tower", STR_THE_TOWER_TITLE)), tr, tg, tb);
                unlocked = true;
                par = 105;
                max_trinkets = 2;
            }
            else
            {
                font::print(PR_2X | PR_CEN, -1, 30, loc::gettext(STR_ID("???", STR_QQQ)), tr, tg, tb);
                font::print(PR_CEN, -1, 60, loc::gettext(STR_ID("TO UNLOCK:", STR_TO_UNLOCK)), tr, tg, tb);
                font::print(PR_CEN, -1, 75, loc::gettext(STR_ID("Rescue Vermilion", STR_RESCUE_VERMILION)), tr, tg, tb);
                font::print(PR_CEN, -1, 87, loc::gettext(STR_ID("Find nine trinkets", STR_FIND_9_TRINKETS)), tr, tg, tb);
            }
            break;
        case 3:
            if (game.unlock[Unlock_TIMETRIAL_SPACESTATION2])
            {
                font::print(PR_2X | PR_CEN, -1, 30, loc::gettext(STR_ID("Space Station 2", STR_SPACE_STATION_2_TITLE)), tr, tg, tb);
                unlocked = true;
                par = 200;
                max_trinkets = 5;
            }
            else
            {
                font::print(PR_2X | PR_CEN, -1, 30, loc::gettext(STR_ID("???", STR_QQQ)), tr, tg, tb);
                font::print(PR_CEN, -1, 60, loc::gettext(STR_ID("TO UNLOCK:", STR_TO_UNLOCK)), tr, tg, tb);
                font::print(PR_CEN, -1, 75, loc::gettext(STR_ID("Rescue Vitellary", STR_RESCUE_VITELLARY)), tr, tg, tb);
                font::print(PR_CEN, -1, 87, loc::gettext(STR_ID("Find twelve trinkets", STR_FIND_12_TRINKETS)), tr, tg, tb);
            }
            break;
        case 4:
            if (game.unlock[Unlock_TIMETRIAL_WARPZONE])
            {
                font::print(PR_2X | PR_CEN, -1, 30, loc::gettext(STR_ID("The Warp Zone", STR_THE_WARP_ZONE_TITLE)), tr, tg, tb);
                unlocked = true;
                par = 120;
                max_trinkets = 1;
            }
            else
            {
                font::print(PR_2X | PR_CEN, -1, 30, loc::gettext(STR_ID("???", STR_QQQ)), tr, tg, tb);
                font::print(PR_CEN, -1, 60, loc::gettext(STR_ID("TO UNLOCK:", STR_TO_UNLOCK)), tr, tg, tb);
                font::print(PR_CEN, -1, 75, loc::gettext(STR_ID("Rescue Verdigris", STR_RESCUE_VERDIGRIS)), tr, tg, tb);
                font::print(PR_CEN, -1, 87, loc::gettext(STR_ID("Find fifteen trinkets", STR_FIND_15_TRINKETS)), tr, tg, tb);
            }
            break;
        case 5:
            if (game.unlock[Unlock_TIMETRIAL_FINALLEVEL])
            {
                font::print(PR_2X | PR_CEN, -1, 30, loc::gettext(STR_ID("The Final Level", STR_THE_FINAL_LEVEL_TITLE)), tr, tg, tb);
                unlocked = true;
                par = 135;
                max_trinkets = 1;
            }
            else
            {
                font::print(PR_2X | PR_CEN, -1, 30, loc::gettext(STR_ID("???", STR_QQQ)), tr, tg, tb);
                font::print(PR_CEN, -1, 60, loc::gettext(STR_ID("TO UNLOCK:", STR_TO_UNLOCK)), tr, tg, tb);
                font::print(PR_CEN, -1, 75, loc::gettext(STR_ID("Complete the game", STR_COMPLETE_THE_GAME)), tr, tg, tb);
                font::print(PR_CEN, -1, 87, loc::gettext(STR_ID("Find eighteen trinkets", STR_FIND_18_TRINKETS)), tr, tg, tb);
            }
            break;
        }

        if (unlocked)
        {
            if (game.besttimes[id_trial] == -1)
            {
                font::print_wrap(PR_CEN, -1, 75, loc::gettext(STR_ID("Not yet attempted", STR_NOT_ATTEMPTED)), tr, tg, tb);
            }
            else
            {
                int sp = SDL_max(10, font::height(0));

                font::print(PR_RTL_XFLIP, 32, 65, loc::gettext(STR_ID("RECORDS", STR_RECORDS)), tr, tg, tb);
                const char* label = loc::gettext(STR_ID("TIME", STR_TIME));
                int label_len = font::len(0, label);
                font::print(PR_RTL_XFLIP, 32, 65+sp, label, tr, tg, tb);
                label = loc::gettext(STR_ID("SHINY", STR_SHINY));
                label_len = SDL_max(label_len, font::len(0, label));
                font::print(PR_RTL_XFLIP, 32, 65+sp*2, label, tr, tg, tb);
                label = loc::gettext(STR_ID("LIVES", STR_LIVES));
                label_len = SDL_max(label_len, font::len(0, label));
                font::print(PR_RTL_XFLIP, 32, 65+sp*3, label, tr, tg, tb);

                char buffer[SCREEN_WIDTH_CHARS + 1];
                help.format_time(buffer, sizeof(buffer), game.besttimes[id_trial], game.bestframes[id_trial], true);
                font::print(PR_RTL_XFLIP, label_len+48, 65+sp, buffer, tr, tg, tb);

                vformat_buf(
                    buffer, sizeof(buffer),
                    loc::gettext(STR_ID("{n_trinkets}/{max_trinkets}", STR_TOTAL_TRINKETS)),
                    "n_trinkets:int, max_trinkets:int",
                    game.besttrinkets[id_trial], max_trinkets
                );
                font::print(PR_RTL_XFLIP, label_len+48, 65+sp*2, buffer, tr, tg, tb);
                font::print(PR_RTL_XFLIP, label_len+48, 65+sp*3, help.String(game.bestlives[id_trial]), tr, tg, tb);


                const char* str_par_time = loc::gettext(STR_ID("PAR TIME", STR_PAR_TIME));
                const std::string par_time = game.timetstring(par);
                const char* str_best_rank = loc::gettext(STR_ID("BEST RANK", STR_BEST_RANK));
                const char* rank;
                switch(game.bestrank[id_trial])
                {
                case 0:
                    rank = loc::gettext(STR_ID("B", STR_B));
                    break;
                case 1:
                    rank = loc::gettext(STR_ID("A", STR_A));
                    break;
                case 2:
                    rank = loc::gettext(STR_ID("S", STR_S));
                    break;
                case 3:
                    rank = loc::gettext(STR_ID("V", STR_V));
                    break;
                default:
                    rank = "?";
                }

                int w[4] = {
                    font::len(0, str_par_time),
                    font::len(0, par_time.c_str()),
                    font::len(0, str_best_rank),
                    font::len(PR_2X, rank)
                };
                int longest_w = 0;
                for (size_t i = 0; i < 4; i++)
                {
                    if (w[i] > longest_w)
                    {
                        longest_w = w[i];
                    }
                }
                int center_x = 288 - longest_w/2;

                font::print(PR_CEN | PR_RTL_XFLIP, center_x, 65, str_par_time, tr, tg, tb);
                font::print(PR_CEN | PR_RTL_XFLIP, center_x, 65+sp, par_time, tr, tg, tb);
                font::print(PR_CEN | PR_RTL_XFLIP, center_x, 65+sp*3, str_best_rank, tr, tg, tb);
                font::print(
                    PR_2X | PR_CEN | PR_RTL_XFLIP,
                    center_x,
                    66+sp*4,
                    rank,
                    225, 225, 225
                );
            }
        }

        break;
    }
    case Menu::gamecompletecontinue:
        font::print(PR_2X | PR_CEN | PR_CJK_HIGH, -1, 25, loc::gettext(STR_ID("Congratulations!", STR_CONGRATS_TITLE)), tr, tg, tb);

        font::print_wrap(PR_CEN, -1, 45, loc::gettext(STR_ID("Your save files have been updated.", STR_SAVES_UPDATED)), tr, tg, tb);

        font::print_wrap(PR_CEN, -1, 110, loc::gettext(STR_ID("If you want to keep exploring the game, select CONTINUE from the play menu.", STR_KEEP_EXPLORING)), tr, tg, tb);
        break;
    case Menu::unlockmenu:
        font::print(PR_2X | PR_CEN, -1, 30, loc::gettext(STR_ID("Unlock Play Modes", STR_UNLOCK_MODES_TITLE)), tr, tg, tb);

        font::print_wrap(PR_CEN, -1, 65, loc::gettext(STR_ID("From here, you may unlock parts of the game that are normally unlocked as you play.", STR_UNLOCK_MODES_DESC_MENU)), tr, tg, tb);
        break;
    case Menu::unlocktimetrial:
        font::print(PR_2X | PR_CEN, -1, 45, loc::gettext(STR_ID("Congratulations!", STR_CONGRATS_TITLE)), tr, tg, tb);

        font::print_wrap(PR_CEN, -1, 125, loc::gettext(STR_ID("You have unlocked a new Time Trial.", STR_UNLOCKED_NEW_TRIAL)), tr, tg, tb);
        break;
    case Menu::unlocktimetrials:
        font::print(PR_2X | PR_CEN, -1, 45, loc::gettext(STR_ID("Congratulations!", STR_CONGRATS_TITLE)), tr, tg, tb);

        font::print_wrap(PR_CEN, -1, 125, loc::gettext(STR_ID("You have unlocked some new Time Trials.", STR_UNLOCKED_NEW_TRIALS)), tr, tg, tb);
        break;
    case Menu::unlocknodeathmode:
        font::print(PR_2X | PR_CEN, -1, 45, loc::gettext(STR_ID("Congratulations!", STR_CONGRATS_TITLE)), tr, tg, tb);

        font::print_wrap(PR_CEN, -1, 125, loc::gettext(STR_ID("You have unlocked No Death Mode.", STR_UNLOCKED_NO_DEATH)), tr, tg, tb);
        break;
    case Menu::unlockflipmode:
        font::print(PR_2X | PR_CEN, -1, 45, loc::gettext(STR_ID("Congratulations!", STR_CONGRATS_TITLE)), tr, tg, tb);

        font::print_wrap(PR_CEN, -1, 125, loc::gettext(STR_ID("You have unlocked Flip Mode.", STR_UNLOCKED_FLIP_MODE)), tr, tg, tb);
        break;
    case Menu::unlockintermission:
        font::print(PR_2X | PR_CEN, -1, 45, loc::gettext(STR_ID("Congratulations!", STR_CONGRATS_TITLE)), tr, tg, tb);

        font::print_wrap(PR_CEN, -1, 125, loc::gettext(STR_ID("You have unlocked the intermission levels.", STR_UNLOCKED_IMS)), tr, tg, tb);
        break;
    case Menu::playerworlds:
        if (game.editor_disabled)
        {
            if (game.currentmenuoption == 1)
            {
                if (SDL_GetHintBoolean("SteamDeck", SDL_FALSE))
                {
                    font::print_wrap(PR_CEN, -1, 180, loc::gettext(STR_ID("The level editor is not currently supported on Steam Deck, as it requires a keyboard and mouse to use.", STR_EDITOR_UNSUPPORTED_DECK)), tr, tg, tb);
                }
                else
                {
                    font::print_wrap(PR_CEN, -1, 180, loc::gettext(STR_ID("The level editor is not currently supported on this device, as it requires a keyboard and mouse to use.", STR_EDITOR_UNSUPPORTED)), tr, tg, tb);
                }
            }
        }
        else
        {
            font::print_wrap(PR_CEN, -1, 180, loc::gettext(STR_ID("To install new player levels, copy the .vvvvvv files to the levels folder.", STR_TO_INSTALL_LEVELS)), tr, tg, tb);
        }
        break;
    case Menu::confirmshowlevelspath:
        font::print_wrap(PR_CEN, -1, 80, loc::gettext(STR_ID("Are you sure you want to show the levels path? This may reveal sensitive information if you are streaming.", STR_WANNA_SHOW_LEVELS_PATH)), tr, tg, tb);
        break;
    case Menu::showlevelspath:
    {
        int next_y = font::print_wrap(PR_CEN, -1, 40, loc::gettext(STR_ID("The levels path is:", STR_LEVELS_PATH)), tr, tg, tb);
        font::print_wrap(0, 0, next_y, FILESYSTEM_getUserLevelDirectory(), tr, tg, tb, 10, 320);
        break;
    }
    case Menu::errorsavingsettings:
        font::print_wrap(PR_CEN, -1, 95, loc::gettext(STR_ID("ERROR: Could not save settings file!", STR_ERR_SAVE_SETTINGS)), tr, tg, tb);
        break;
    case Menu::errorloadinglevel:
    {
        const char* message;
        if (FILESYSTEM_levelDirHasError())
        {
            message = FILESYSTEM_getLevelDirError();
        }
        else
        {
            message = loc::gettext(STR_ID("Something went wrong, but we forgot the error message.", STR_MISSING_ERROR));
        }
        font::print(PR_2X | PR_CEN | PR_CJK_HIGH, -1, 45, loc::gettext(STR_ID("ERROR", STR_ERROR)), tr, tg, tb);
        font::print_wrap(PR_CEN, -1, 65, message, tr, tg, tb);
        break;
    }
    case Menu::warninglevellist:
    {
        const char* message;
        if (FILESYSTEM_levelDirHasError())
        {
            message = FILESYSTEM_getLevelDirError();
        }
        else
        {
            message = loc::gettext(STR_ID("Something went wrong, but we forgot the error message.", STR_MISSING_ERROR));
        }
        font::print(PR_2X | PR_CEN | PR_CJK_HIGH, -1, 45, loc::gettext(STR_ID("WARNING", STR_WARNING)), tr, tg, tb);
        font::print_wrap(PR_CEN, -1, 65, message, tr, tg, tb);
        break;
    }
    default:
        break;
    }
}

void titlerender(void)
{
    #ifndef __NDS__
    graphics.clear();
    #endif
    if (!game.menustart)
    {
        tr = graphics.col_tr;
        tg = graphics.col_tg;
        tb = graphics.col_tb;

        int temp = 50;
        graphics.draw_sprite((160 - 96) + 0 * 32, temp, 23, tr, tg, tb);
        graphics.draw_sprite((160 - 96) + 1 * 32, temp, 23, tr, tg, tb);
        graphics.draw_sprite((160 - 96) + 2 * 32, temp, 23, tr, tg, tb);
        graphics.draw_sprite((160 - 96) + 3 * 32, temp, 23, tr, tg, tb);
        graphics.draw_sprite((160 - 96) + 4 * 32, temp, 23, tr, tg, tb);
        graphics.draw_sprite((160 - 96) + 5 * 32, temp, 23, tr, tg, tb);
#if defined(MAKEANDPLAY)
        font::print(PR_RIGHT, 264, temp+35, loc::gettext(STR_ID("MAKE AND PLAY EDITION", STR_MAKE_AND_PLAY)), tr, tg, tb);
#endif

        char buffer[SCREEN_WIDTH_CHARS*2 + 1];
        vformat_buf(
            buffer, sizeof(buffer),
            loc::gettext(STR_ID("[ Press {button} to Start ]", STR_PROMPT_START)),
            "button:but",
            vformat_button(ActionSet_Menu, Action_Menu_Accept)
        );
        font::print_wrap(PR_CEN, -1, 175, buffer, tr, tg, tb);
        if (BUTTONGLYPHS_keyboard_is_active())
        {
            font::print_wrap(PR_CEN, -1, 195, loc::gettext(STR_ID("ACTION = Space, Z, or V", STR_ACTION_IS)), int(tr*0.5f), int(tg*0.5f), int(tb*0.5f));
        }
    }
    else
    {
        #ifdef __NDS__
        if(!game.colourblindmode && game.gamestate != GAMEMODE) {
            graphics.drawtowerbackground(graphics.titlebg);
        }
        else {
            graphics.clear_tile_layer(true);
        }
        #else
        if(!game.colourblindmode) graphics.drawtowerbackground(graphics.titlebg);
        #endif

        tr = graphics.col_tr;
        tg = graphics.col_tg;
        tb = graphics.col_tb;

        menurender();

        tr = int(tr * .8f);
        tg = int(tg * .8f);
        tb = int(tb * .8f);
        if (tr < 0) tr = 0;
        if(tr>255) tr=255;
        if (tg < 0) tg = 0;
        if(tg>255) tg=255;
        if (tb < 0) tb = 0;
        if(tb>255) tb=255;
        graphics.drawmenu(tr, tg, tb, game.currentmenuname);
    }

    graphics.drawfade();

    graphics.renderwithscreeneffects();

    #ifdef __NDS__
    if (graphics.foregrounddrawn) {
        graphics.clear_tile_layer(false);
        graphics.foregrounddrawn = false;
    }
    if (graphics.subscreendrawn) {
        graphics.clear_sub();
        graphics.subscreendrawn = false;
    }
    #endif
}

void gamecompleterender(void)
{
    #ifdef __NDS__
    if (graphics.foregrounddrawn) {
        graphics.clear_tile_layer(false);
        graphics.foregrounddrawn = false;
    }
    if (game.creditposition == 0) {
        graphics.titlebg.tdrawback = true;
    }
    #else
    graphics.clear();
    #endif

    if(!game.colourblindmode) graphics.drawtowerbackground(graphics.titlebg);
    #ifdef __NDS__
    else graphics.clear_tile_layer(true);
    #endif

    tr = graphics.col_tr;
    tg = graphics.col_tg;
    tb = graphics.col_tb;


    //rendering starts... here!

    int position = graphics.lerp(game.oldcreditposition, game.creditposition);
    if (graphics.onscreen(220 + position))
    {
        int temp = 220 + position;
        graphics.draw_sprite((160 - 96) + 0 * 32, temp, 23, tr, tg, tb);
        graphics.draw_sprite((160 - 96) + 1 * 32, temp, 23, tr, tg, tb);
        graphics.draw_sprite((160 - 96) + 2 * 32, temp, 23, tr, tg, tb);
        graphics.draw_sprite((160 - 96) + 3 * 32, temp, 23, tr, tg, tb);
        graphics.draw_sprite((160 - 96) + 4 * 32, temp, 23, tr, tg, tb);
        graphics.draw_sprite((160 - 96) + 5 * 32, temp, 23, tr, tg, tb);
    }

    if (graphics.onscreen(290 + position)) font::print(PR_2X | PR_CEN, -1, 290 + position, loc::gettext(STR_ID("Starring", STR_STARRING)), tr, tg, tb);

    if (graphics.onscreen(320 + position))
    {
        graphics.drawcrewman(70, 320 + position, 0, true);
        font::print(0, 100, 330 + position, loc::gettext(STR_ID("Captain Viridian", STR_CPT_VIRIDIAN)), tr, tg, tb);
    }
    if (graphics.onscreen(350 + position))
    {
        graphics.drawcrewman(70, 350 + position, 1, true);
        font::print(0, 100, 360 + position, loc::gettext(STR_ID("Doctor Violet", STR_DR_VIOLET)), tr, tg, tb);
    }
    if (graphics.onscreen(380 + position))
    {
        graphics.drawcrewman(70, 380 + position, 2, true);
        font::print(0, 100, 390 + position, loc::gettext(STR_ID("Professor Vitellary", STR_PROF_VITELLARY)), tr, tg, tb);
    }
    if (graphics.onscreen(410 + position))
    {
        graphics.drawcrewman(70, 410 + position, 3, true);
        font::print(0, 100, 420 + position, loc::gettext(STR_ID("Officer Vermilion", STR_OFC_VERMILION)), tr, tg, tb);
    }
    if (graphics.onscreen(440 + position))
    {
        graphics.drawcrewman(70, 440 + position, 4, true);
        font::print(0, 100, 450 + position, loc::gettext(STR_ID("Chief Verdigris", STR_CHF_VERDIGRIS)), tr, tg, tb);
    }
    if (graphics.onscreen(470 + position))
    {
        graphics.drawcrewman(70, 470 + position, 5, true);
        font::print(0, 100, 480 + position, loc::gettext(STR_ID("Doctor Victoria", STR_DR_VICTORIA)), tr, tg, tb);
    }

    if (graphics.onscreen(520 + position))
    {
        uint32_t flag = PR_3X;
        const char* text = loc::gettext(STR_ID("Credits", STR_CREDITS_TITLE));
        if (font::len(flag, text) > SCREEN_WIDTH_PIXELS)
        {
            flag = PR_2X;
        }
        font::print(flag | PR_CEN, -1, 520 + position, text, tr, tg, tb);
    }

    if (graphics.onscreen(560 + position))
    {
        font::print(PR_CJK_HIGH, 40, 560 + position, loc::gettext(STR_ID("Created by", STR_CREATED_BY)), tr, tg, tb);
        font::print(PR_2X | PR_FONT_8X8, 60, 570 + position, "Terry Cavanagh", tr, tg, tb);
    }

    if (graphics.onscreen(600 + position))
    {
        font::print(PR_CJK_HIGH, 40, 600 + position, loc::gettext(STR_ID("With Music by", STR_WITH_MUSIC_BY)), tr, tg, tb);
        font::print(PR_2X | PR_FONT_8X8, 60, 610 + position, "Magnus Pålsson", tr, tg, tb);
    }

    if (graphics.onscreen(640 + position))
    {
        font::print(PR_CJK_HIGH, 40, 640 + position, loc::gettext(STR_ID("Rooms Named by", STR_ROOMS_NAMED_BY)), tr, tg, tb);
        font::print(PR_2X | PR_FONT_8X8, 60, 650 + position, "Bennett Foddy", tr, tg, tb);
    }

    if (graphics.onscreen(710 + position))
    {
        font::print(PR_CJK_HIGH, 40, 680 + position, loc::gettext(STR_ID("C++ Port by", STR_CPP_PORT_BY)), tr, tg, tb);
        font::print(PR_2X | PR_FONT_8X8, 60, 690 + position, "Simon Roth", tr, tg, tb);
        font::print(PR_2X | PR_FONT_8X8, 60, 710 + position, "Ethan Lee", tr, tg, tb);
        font::print(PR_2X | PR_FONT_8X8, 60, 730 + position, "Misa Kai", tr, tg, tb);
    }


    if (graphics.onscreen(770 + position))
    {
        font::print(PR_CJK_HIGH, 40, 760 + position, loc::gettext(STR_ID("Beta Testing by", STR_BETA_TESTED_BY)), tr, tg, tb);
        font::print(PR_2X | PR_FONT_8X8, 60, 770 + position, "Sam Kaplan", tr, tg, tb);
        font::print(PR_2X | PR_FONT_8X8, 60, 790 + position, "Pauli Kohberger", tr, tg, tb);
    }

    if (graphics.onscreen(820 + position))
    {
        font::print(PR_CJK_HIGH, 40, 820 + position, loc::gettext(STR_ID("Ending Picture by", STR_END_PICTURE_BY)), tr, tg, tb);
        font::print(PR_2X | PR_FONT_8X8, 60, 830 + position, "Pauli Kohberger", tr, tg, tb);
    }

    int creditOffset = 890;

    if (graphics.onscreen(creditOffset + position))
    {
        font::print(PR_2X | PR_CJK_HIGH | PR_CEN, -1, creditOffset + position, loc::gettext(STR_ID("Localisation", STR_LOCALISATION)), tr, tg, tb);
    }
    creditOffset += 30;

    if (graphics.onscreen(creditOffset + position))
    {
        const char* text = loc::gettext(STR_ID("Localisation Project Led by", STR_LOCALIZED_LED_BY));
        int x = SCREEN_WIDTH_PIXELS - font::len(0, text);
        x = SDL_min(x, 40);
        font::print(PR_CJK_HIGH, x, creditOffset + position, text, tr, tg, tb);
        font::print(PR_2X | PR_FONT_8X8, 60, creditOffset + position + 10, "Dav999", tr, tg, tb);
    }
    creditOffset += 40;
    if (graphics.onscreen(creditOffset + position))
    {
        const char* text = loc::gettext(STR_ID("Pan-European Font Design by", STR_PE_FONT_BY));
        int x = SCREEN_WIDTH_PIXELS - font::len(0, text);
        x = SDL_min(x, 40);
        font::print(PR_CJK_HIGH, x, creditOffset + position, text, tr, tg, tb);
        font::print(PR_2X | PR_FONT_8X8, 60, creditOffset + position + 10, "Reese Rivers", tr, tg, tb);
    }
    creditOffset += 40;
    if (graphics.onscreen(creditOffset + position))
    {
        const char* text = loc::gettext(STR_ID("With contributions on GitHub from", STR_WITH_CONTRIB_FROM));
        int x = SCREEN_WIDTH_PIXELS - font::len(0, text);
        x = SDL_min(x, 40);
        font::print(PR_CJK_HIGH, x, creditOffset + position, text, tr, tg, tb);
        font::print(PR_2X | PR_FONT_8X8, 60, creditOffset + position + 10, "Alexandra Fox", tr, tg, tb);
        font::print(PR_2X | PR_FONT_8X8, 60, creditOffset + position + 30, "mothbeanie", tr, tg, tb);
    }
    creditOffset += 100;
    if (graphics.onscreen(creditOffset + position))
    {
        font::print(PR_2X | PR_CJK_HIGH | PR_CEN, -1, creditOffset + position, loc::gettext(STR_ID("Translators", STR_TRANSLATORS)), tr, tg, tb);
    }
    creditOffset += 40;
    for (size_t i = 0; i < SDL_arraysize(Credits::translators); i += 1)
    {
        if (graphics.onscreen(creditOffset + position))
        {
            if (Credits::translators[i][0] == '>')
            {
                // Category heading, remove the > character and translate the rest
                font::print(0, 76, creditOffset + position, loc::gettext(STR_ID(&Credits::translators[i][1], Credits::translators[i][1] == 'E' ? STR_EDITING_LQA : STR_TRANSLATORS)), tr, tg, tb);
            }
            else if (Credits::translators[i][0] != ' ')
            {
                // Not prefixed with a space, so this line is the name of a language, display its localised string
                font::print(0, 60, creditOffset + position, loc::gettext(STR_ID(Credits::translators[i], lang_to_id(Credits::translators[i]))), tr, tg, tb);
            }
            else
            {
                // Otherwise, this line is the name of a translator, indent it and display with the original 8x8 font always
                font::print(PR_FONT_8X8, 72, creditOffset + position, Credits::translators[i], tr, tg, tb);
            }
        }
        creditOffset += 12;
    }

    creditOffset += 40;

    if (graphics.onscreen(creditOffset + position))
    {
        font::print(PR_3X | PR_CEN, -1, creditOffset + position, loc::gettext(STR_ID("Patrons", STR_PATRONS)), tr, tg, tb);
    }

    creditOffset += 50;

    for (size_t i = 0; i < SDL_arraysize(Credits::superpatrons); i += 1)
    {
        if (graphics.onscreen(creditOffset + position))
        {
            font::print(PR_CEN | PR_FONT_8X8, -1, creditOffset + position, Credits::superpatrons[i], tr, tg, tb);
        }
        creditOffset += 10;
    }

    creditOffset += 10;
    if (graphics.onscreen(creditOffset + position))
    {
        font::print(PR_CEN, -1, creditOffset + position, loc::gettext(STR_ID("and", STR_AND)), tr, tg, tb);
    }
    creditOffset += 20;

    for (size_t i = 0; i < SDL_arraysize(Credits::patrons); i += 1)
    {
        if (graphics.onscreen(creditOffset + position))
        {
            font::print(PR_CEN | PR_FONT_8X8, -1, creditOffset + position, Credits::patrons[i], tr, tg, tb);
        }
        creditOffset += 10;
    }

    creditOffset += 20;
    if (graphics.onscreen(creditOffset + position))
    {
        font::print(PR_2X | PR_CEN, -1, creditOffset + position, loc::gettext(STR_ID("GitHub Contributors", STR_GH_CONTRIBUTORS)), tr, tg, tb);
    }
    creditOffset += 30;

    for (size_t i = 0; i < SDL_arraysize(Credits::githubfriends); i += 1)
    {
        if (graphics.onscreen(creditOffset + position))
        {
            font::print(PR_CEN | PR_FONT_8X8, -1, creditOffset + position, Credits::githubfriends[i], tr, tg, tb);
        }
        creditOffset += 10;
    }

    creditOffset += 140;
    if (graphics.onscreen(creditOffset + position))
    {
        const char* line1;
        const char* line2;
        if (graphics.flipmode)
        {
            line1 = loc::gettext(STR_ID("playing!", STR_PLAYING));
            line2 = loc::gettext(STR_ID("Thanks for", STR_THANKS_FOR));
        }
        else
        {
            line1 = loc::gettext(STR_ID("Thanks for", STR_THANKS_FOR));
            line2 = loc::gettext(STR_ID("playing!", STR_PLAYING));
        }
        font::print(PR_2X | PR_CEN | PR_CJK_HIGH, -1, creditOffset + position, line1, tr, tg, tb);
        creditOffset += 20;
        font::print(PR_2X | PR_CEN | PR_CJK_LOW, -1, creditOffset + position, line2, tr, tg, tb);
    }

    draw_skip_message();

    graphics.drawfade();

    graphics.render();

    #ifdef __NDS__
    if (graphics.subscreendrawn) {
        graphics.clear_sub();
        graphics.subscreendrawn = false;
    }
    #endif
}

void gamecompleterender2(void)
{
    #ifdef __NDS__
    graphics.copy_texture(graphics.images[IMAGE_ENDING], NULL, NULL); // ensure it will fit to screen
    #else
    graphics.clear();

    graphics.drawimage(IMAGE_ENDING, 0, 0);
    #endif

    for (int j = 0; j < 30; j++)
    {
        for (int i = 0; i < 40; i++)
        {
            if (j == game.creditposy)
            {
                if (i > game.creditposx)
                {
                    graphics.fill_rect(i * 8, j * 8, 8, 8, 0, 0, 0);
                }
            }

            if (j > game.creditposy)
            {
                graphics.fill_rect(i * 8, j * 8, 8, 8, 0, 0, 0);
            }
        }
    }

    graphics.fill_rect(graphics.lerp(game.oldcreditposx * 8, game.creditposx * 8) + 8, game.creditposy * 8, 8, 8, 0, 0, 0);

    draw_skip_message();

    graphics.drawfade();

    graphics.render();

    #ifdef __NDS__
    if (graphics.subscreendrawn) {
        graphics.clear_sub();
        graphics.subscreendrawn = false;
    }
    #endif
}

static const char* interact_prompt(
    char* buffer,
    const size_t buffer_size,
    const char* raw
) {
    vformat_buf(
        buffer, buffer_size,
        raw,
        "button:but",
        vformat_button(ActionSet_InGame, Action_InGame_Interact)
    );

    return buffer;
}

static void mode_indicator_text(const int alpha)
{
    const uint32_t flags = PR_BRIGHTNESS(alpha) | PR_BOR | PR_RTL_XFLIP;
    const int r = 220 - help.glow;
    const int g = 220 - help.glow;
    const int b = 255 - help.glow/2;
    const int x = 5;
    const int spacing = font::height(flags) + 2;
    int y = 5;
    if (game.advancetext)
    {
        /* Prevent clashing */
        y = 20;
    }
    if ((game.act_fade > 5 || game.prev_act_fade > 5) && game.activity_y < 60)
    {
        /* Prevent clashing */
        y = game.activity_y + 37;
    }

    /* FIXME: Some strings have not yet been translated. In order to not have
     * English text in other languages, they are substituted with existing
     * ones. Remove all substitute text when they're fully translated. */

    if (map.invincibility)
    {
        const char* english = "Invincibility mode enabled";
        const char* text = loc::gettext(STR_ID(english, STR_INVINCIBILITY_ENABLED));
        if (loc::lang != "en" && SDL_strcmp(english, text) == 0)
        {
            /* Substitute text */
            text = loc::gettext(STR_ID("Invincibility", STR_INVINCIBILITY_TITLE));
        }
        font::print(flags, x, y, text, r, g, b);
        y += spacing;
    }

    enum GlitchrunnerMode mode = GlitchrunnerMode_get();
    if (mode != GlitchrunnerNone)
    {
        char buffer[SCREEN_WIDTH_CHARS + 1];
        const char* english = "Glitchrunner mode enabled ({version})";
        const char* text = loc::gettext(STR_ID(english, STR_GLITCH_ENABLED_VERSION));
        if (loc::lang != "en" && SDL_strcmp(english, text) == 0)
        {
            /* Substitute text */
            SDL_strlcpy(buffer, loc::gettext(STR_ID("Glitchrunner Mode", STR_GLITCH_TITLE)), sizeof(buffer));
        }
        else
        {
            const char* mode_string = loc::gettext(STR_ID(GlitchrunnerMode_enum_to_string(mode), (String_ID)(STR_GLITCH_NONE + mode)));
            vformat_buf(buffer, sizeof(buffer), text, "version:str", mode_string);
        }
        font::print(flags, x, y, buffer, r, g, b);
        y += spacing;
    }

    if (graphics.flipmode)
    {
        const char* english = "Flip Mode enabled";
        const char* text = loc::gettext(STR_ID(english, STR_FLIP_MODE_ENABLED));
        if (loc::lang != "en" && SDL_strcmp(english, text) == 0)
        {
            /* Substitute text */
            text = loc::gettext(STR_ID("Flip Mode", STR_FLIP_MODE_TITLE));
        }
        font::print(flags, x, y, text, r, g, b);
        y += spacing;
    }

    switch (game.slowdown)
    {
    case 24:
        font::print(flags, x, y, loc::gettext(STR_ID("Game speed is at 80%", STR_SPEED_IS_80)), r, g, b);
        y += spacing;
        break;
    case 18:
        font::print(flags, x, y, loc::gettext(STR_ID("Game speed is at 60%", STR_SPEED_IS_60)), r, g, b);
        y += spacing;
        break;
    case 12:
        font::print(flags, x, y, loc::gettext(STR_ID("Game speed is at 40%", STR_SPEED_IS_40)), r, g, b);
        y += spacing;
    }
}

#ifdef __NDS__
static void rendermap_sub(bool blinkCursor) {
    gameScreen.setupSubscreenLayer(graphics.flipmode);
    bool noSignal = map.finalmode || (map.custommode && !map.customshowmm);
    for (int j = 0; j < map.getheight(); j++) {
        for (int i = 0; i < map.getwidth(); i++) {
            graphics.draw_minimap_cell_sub(i, j, !noSignal && map.isexplored(i, j));
        }
    }
    
    if (noSignal) {
        graphics.hide_cursor_sub();
        graphics.clear_sprites_sub(8, 2 + 40);
        graphics.subscreendrawn = true;
        return;
    }

    if ((!script.running || game.gamestate != GAMEMODE) && (game.noflashingmode || !blinkCursor || (map.cursordelay / 15) % 2 == 0)) {
        graphics.draw_cursor_sub(game.roomx - 100, game.roomy - 100, 16, 245 - help.glow, 245 - help.glow);
    }
    else {
        graphics.hide_cursor_sub();
    }

    static int usedSlots = 0;
    int slot = 0;
    const int legendSlotOffset = 10;
    for (size_t i = 0; i < map.teleporters.size(); i++) {
        if (map.showteleporters && map.isexplored(map.teleporters[i].x, map.teleporters[i].y)) {
            graphics.draw_legend_icon_sub(legendSlotOffset + slot++, map.teleporters[i].x, map.teleporters[i].y, 1);
        }
        else if (map.showtargets && !map.isexplored(map.teleporters[i].x, map.teleporters[i].y)) {
            graphics.draw_legend_icon_sub(legendSlotOffset + slot++, map.teleporters[i].x, map.teleporters[i].y, 0);
        }
    }
    if (map.showtrinkets) {
        for (size_t i = 0; i < map.shinytrinkets.size(); i++) {
            if (!obj.collect[i]) {
                graphics.draw_legend_icon_sub(legendSlotOffset + slot++, map.shinytrinkets[i].x, map.shinytrinkets[i].y, 3);
            }
        }
    }
    if (usedSlots > slot) {
        graphics.clear_sprites_sub(legendSlotOffset + slot, usedSlots - slot);
    }
    usedSlots = slot;
    graphics.clear_sprites_sub(8, 2); // clear teleporter menu sprites in case they were used

    graphics.subscreendrawn = true;
}
#endif

void gamerender(void)
{
    #ifdef __NDS__
    if (game.screenshake > 0 && !game.noflashingmode)
    {
        graphics.screenshakescroll();
    }
    #else
    graphics.set_render_target(graphics.gameplayTexture);
    #endif
    graphics.set_color(0, 0, 0, 255);

    if(!game.blackout)
    {
        if (map.towermode)
        {
            if (!game.colourblindmode)
            {
                graphics.drawtowerbackground(graphics.towerbg);
            }
            else
            {
                #ifdef __NDS__
                graphics.clear_tile_layer(true);
                #else
                graphics.clear();
                #endif
            }
            graphics.drawtowermap();
        }
        else
        {
            if(!game.colourblindmode)
            {
                graphics.drawbackground(map.background);
            }
            else
            {
                #ifdef __NDS__
                graphics.clear_tile_layer(true);
                #else
                graphics.clear();
                #endif
            }
            if ((map.finalmode || map.custommode) && map.final_colormode)
            {
                graphics.drawfinalmap();
            }
            else
            {
                graphics.drawmap();
            }
        }


        graphics.drawentities();
        if (map.towermode)
        {
            graphics.drawtowerspikes();
        }
    }

    int return_editor_alpha = 0;
    bool draw_return_editor_text = false;
    #ifndef __NDS__
    if (map.custommode && !map.custommodeforreal && !game.advancetext)
    {
        return_editor_alpha = graphics.lerp(
            ed.old_return_message_timer, ed.return_message_timer
        );
        draw_return_editor_text = return_editor_alpha > 100;
    }
    #endif

    int mode_indicator_alpha = graphics.lerp(
        game.old_mode_indicator_timer, game.mode_indicator_timer
    );
    bool any_mode_active = map.invincibility
        || GlitchrunnerMode_get() != GlitchrunnerNone
        || graphics.flipmode
        || game.slowdown < 30;
    bool draw_mode_indicator_text = mode_indicator_alpha > 100 && any_mode_active;

    if (graphics.fademode == FADE_NONE
    && !game.intimetrial
    && !game.isingamecompletescreen()
    && (!game.swnmode || game.swngame != SWN_SUPERGRAVITRON)
    && game.showingametimer
    && !roomname_translator::enabled
    && (!game.swnmode || game.swngame != SWN_START_GRAVITRON_STEP_3)
    && obj.trophytext <= 0 && obj.oldtrophytext <= 0
    && !draw_return_editor_text
    && !draw_mode_indicator_text)
    {
        const char* tempstring = loc::gettext(STR_ID("TIME:", STR_TRIAL_TIME));
        int label_len = font::len(0, tempstring);
        font::print(PR_BOR | PR_RTL_XFLIP, 6, 6, tempstring, 255,255,255);
        char buffer[SCREEN_WIDTH_CHARS + 1];
        game.timestringcenti(buffer, sizeof(buffer));
        font::print(PR_BOR | PR_RTL_XFLIP, 6+label_len, 6, buffer, 196,196,196);
    }

    bool force_roomname_hidden = false;
    bool roomname_untranslated = false;
    int roomname_r = 196, roomname_g = 196, roomname_b = 255 - help.glow;
    if (roomname_translator::enabled)
    {
        roomname_translator::overlay_render(
            &force_roomname_hidden,
            &roomname_untranslated,
            &roomname_r, &roomname_g, &roomname_b
        );
    }

    if ((map.extrarow==0 || (map.custommode && map.roomname[0] != '\0')) && !force_roomname_hidden)
    {
        const char* roomname = loc::gettext_roomname(map.custommode, game.roomx, game.roomy, map.roomname, map.roomname_special);

        graphics.render_roomname(
            roomname_untranslated ? PR_FONT_8X8 : PR_FONT_LEVEL,
            roomname,
            roomname_r, roomname_g, roomname_b
        );
    }

    if (map.roomtexton)
    {
        //Draw room text!
        for (size_t i = 0; i < map.roomtext.size(); i++)
        {
            graphics.print_roomtext(map.roomtext[i].x*8, map.roomtext[i].y*8, map.roomtext[i].text, map.roomtext[i].rtl);
        }
    }

    if (draw_return_editor_text)
    {
        char buffer[SCREEN_WIDTH_CHARS + 1];
        vformat_buf(
            buffer, sizeof(buffer),
            loc::gettext(STR_ID("[Press {button} to return to editor]", STR_PROMPT_RETURN_TO_ED)),
            "button:but",
            vformat_button(ActionSet_InGame, Action_InGame_Map)
        );
        font::print(
            PR_BRIGHTNESS(return_editor_alpha) | PR_BOR,
            5, 5, buffer,
            220 - (help.glow), 220 - (help.glow), 255 - (help.glow / 2)
        );
    }

    graphics.cutscenebars();
    graphics.drawfade();

    graphics.drawgui();

    if (draw_mode_indicator_text && !draw_return_editor_text)
    {
        mode_indicator_text(mode_indicator_alpha);
    }

    #ifndef __NDS__
    graphics.set_render_target(graphics.gameTexture);

    graphics.copy_texture(graphics.gameplayTexture, NULL, NULL);
    #endif

    if (game.advancetext)
    {
        char buffer_adv[SCREEN_WIDTH_CHARS + 1];
        vformat_buf(
            buffer_adv, sizeof(buffer_adv),
            loc::gettext(STR_ID("- Press {button} to advance text -", STR_PROMPT_ADVANCE_TEXT)),
            "button:but",
            vformat_button(ActionSet_InGame, Action_InGame_ACTION)
        );

        font::print(PR_CEN | PR_BOR, -1, graphics.flipmode ? 228 : 5, buffer_adv, 220 - (help.glow), 220 - (help.glow), 255 - (help.glow / 2));
    }

    if (game.readytotele > 100 || game.oldreadytotele > 100)
    {
        char buffer[SCREEN_WIDTH_CHARS + 1];
        const char* final_string = interact_prompt(
            buffer,
            sizeof(buffer),
            loc::gettext(STR_ID("- Press {button} to Teleport -", STR_PROMPT_TELEPORT_2))
        );
        int alpha = graphics.lerp(game.oldreadytotele, game.readytotele);

        font::print(
            PR_BRIGHTNESS(alpha) | PR_CEN | PR_BOR,
            -1,
            graphics.flipmode ? 20 : 210,
            final_string,
            235 - (help.glow / 2),
            235 - (help.glow / 2),
            255
        );
    }

    if (game.swnmode)
    {
        if (game.swngame == SWN_GRAVITRON)
        {
            std::string tempstring = help.timestring(game.swntimer);
            font::print(PR_2X | PR_CEN | PR_BOR, -1, 20, tempstring, 220 - (help.glow), 220 - (help.glow), 255 - (help.glow / 2));
        }
        else if (game.swngame == SWN_SUPERGRAVITRON)
        {
            if (game.swnmessage == 0)
            {
                std::string tempstring = help.timestring(game.swntimer);
                font::print(PR_BOR, 10, 10, loc::gettext(STR_ID("Current Time", STR_CURRENT_TIME)), 220 - (help.glow), 220 - (help.glow), 255 - (help.glow / 2));
                font::print(PR_2X | PR_BOR | PR_FONT_8X8, 25, 24, tempstring, 220 - (help.glow), 220 - (help.glow), 255 - (help.glow / 2));
                tempstring = help.timestring(game.swnrecord);
                font::print(PR_BOR | PR_RIGHT, 320-8, 10, loc::gettext(STR_ID("Best Time", STR_BEST_TIME)), 220 - (help.glow), 220 - (help.glow), 255 - (help.glow / 2));
                font::print(PR_2X | PR_BOR | PR_FONT_8X8 | PR_RIGHT, 300, 24, tempstring, 220 - (help.glow), 220 - (help.glow), 255 - (help.glow / 2));

                switch(game.swnbestrank)
                {
                case 0:
                    font::print_wrap(PR_CEN, -1, 204, loc::gettext(STR_ID("Next Trophy at 5 seconds", STR_NEXT_TROPHY_5_SECONDS)), 220 - (help.glow), 220 - (help.glow), 255 - (help.glow / 2));
                    break;
                case 1:
                    font::print_wrap(PR_CEN, -1, 204, loc::gettext(STR_ID("Next Trophy at 10 seconds", STR_NEXT_TROPHY_10_SECONDS)), 220 - (help.glow), 220 - (help.glow), 255 - (help.glow / 2));
                    break;
                case 2:
                    font::print_wrap(PR_CEN, -1, 204, loc::gettext(STR_ID("Next Trophy at 15 seconds", STR_NEXT_TROPHY_15_SECONDS)), 220 - (help.glow), 220 - (help.glow), 255 - (help.glow / 2));
                    break;
                case 3:
                    font::print_wrap(PR_CEN, -1, 204, loc::gettext(STR_ID("Next Trophy at 20 seconds", STR_NEXT_TROPHY_20_SECONDS)), 220 - (help.glow), 220 - (help.glow), 255 - (help.glow / 2));
                    break;
                case 4:
                    font::print_wrap(PR_CEN, -1, 204, loc::gettext(STR_ID("Next Trophy at 30 seconds", STR_NEXT_TROPHY_30_SECONDS)), 220 - (help.glow), 220 - (help.glow), 255 - (help.glow / 2));
                    break;
                case 5:
                    font::print_wrap(PR_CEN, -1, 204, loc::gettext(STR_ID("Next Trophy at 1 minute", STR_NEXT_TROPHY_1_MINUTE)), 220 - (help.glow), 220 - (help.glow), 255 - (help.glow / 2));
                    break;
                case 6:
                    font::print_wrap(PR_CEN, -1, 204, loc::gettext(STR_ID("All Trophies collected!", STR_GOT_ALL_TROPHIES)), 220 - (help.glow), 220 - (help.glow), 255 - (help.glow / 2));
                    break;
                }
            }
            else if (game.swnmessage == 1)
            {
                std::string tempstring = help.timestring(game.swntimer);
                font::print(PR_BOR, 10, 10, loc::gettext(STR_ID("Current Time", STR_CURRENT_TIME)), 220 - (help.glow), 220 - (help.glow), 255 - (help.glow / 2));
                font::print(PR_2X | PR_BOR | PR_FONT_8X8, 25, 24, tempstring, 220 - (help.glow), 220 - (help.glow), 255 - (help.glow / 2));
                tempstring = help.timestring(game.swnrecord);
                if (int(game.deathseq / 5) % 2 == 1)
                {
                    font::print(PR_BOR | PR_RIGHT, 320-8, 10, loc::gettext(STR_ID("Best Time", STR_BEST_TIME)), 220 - (help.glow), 220 - (help.glow), 255 - (help.glow / 2));
                    font::print(PR_2X | PR_BOR | PR_FONT_8X8 | PR_RIGHT, 300, 24, tempstring, 128 - (help.glow), 220 - (help.glow), 128 - (help.glow / 2));

                    font::print(PR_2X | PR_BOR | PR_CEN, -1, 200, loc::gettext(STR_ID("New Record!", STR_NEW_RECORD)), 128 - (help.glow), 220 - (help.glow), 128 - (help.glow / 2));
                }
            }
            else if (game.swnmessage >= 2)
            {
                game.swnmessage--;
                if (game.swnmessage == 2) game.swnmessage = 0;
                std::string tempstring = help.timestring(game.swntimer);
                font::print(PR_BOR, 10, 10, loc::gettext(STR_ID("Current Time", STR_CURRENT_TIME)), 220 - (help.glow), 220 - (help.glow), 255 - (help.glow / 2));
                font::print(PR_2X | PR_BOR | PR_FONT_8X8, 25, 24, tempstring, 220 - (help.glow), 220 - (help.glow), 255 - (help.glow / 2));
                tempstring = help.timestring(game.swnrecord);
                font::print(PR_BOR | PR_RIGHT, 320-8, 10, loc::gettext(STR_ID("Best Time", STR_BEST_TIME)), 220 - (help.glow), 220 - (help.glow), 255 - (help.glow / 2));
                font::print(PR_2X | PR_BOR | PR_FONT_8X8 | PR_RIGHT, 300, 24, tempstring, 220 - (help.glow), 220 - (help.glow), 255 - (help.glow / 2));

                if (int(game.swnmessage / 5) % 2 == 1)
                {
                    font::print(PR_2X | PR_BOR | PR_CEN, -1, 200, loc::gettext(STR_ID("New Trophy!", STR_NEW_TROPHY)), 220 - (help.glow), 128 - (help.glow), 128 - (help.glow / 2));
                }
            }

            char buffer[SCREEN_WIDTH_CHARS + 1];
            vformat_buf(
                buffer, sizeof(buffer),
                loc::gettext(STR_ID("[Press {button} to stop]", STR_PROMPT_STOP)),
                "button:but",
                vformat_button(ActionSet_InGame, Action_InGame_Map)
            );
            font::print(PR_BOR | PR_CEN, -1, 228, buffer, 160 - (help.glow/2), 160 - (help.glow/2), 160 - (help.glow/2));
        }
        else if (game.swngame == SWN_START_GRAVITRON_STEP_3)
        {
            if (int(game.swndelay / 15) % 2 == 1 || game.swndelay >= 120)
            {
                int y1;
                int y2;
                if (graphics.flipmode)
                {
                    y1 = 30;
                    y2 = 10;
                }
                else
                {
                    y1 = 10;
                    y2 = 30;
                }
                font::print(PR_2X | PR_CEN | PR_BOR | PR_CJK_HIGH, -1, y1, loc::gettext(STR_ID("Survive for", STR_SURVIVE_FOR)), 220 - (help.glow), 220 - (help.glow), 255 - (help.glow / 2));
                font::print(PR_2X | PR_CEN | PR_BOR, -1, y2, loc::gettext(STR_ID("60 seconds!", STR_60_SECONDS)), 220 - (help.glow), 220 - (help.glow), 255 - (help.glow / 2));
            }
        }
        else if (game.swngame == SWN_START_SUPERGRAVITRON_STEP_2)
        {
            if (game.swndelay >= 60)
            {
                font::print(PR_2X | PR_BOR | PR_CEN, -1, 20, loc::gettext(STR_ID("SUPER GRAVITRON", STR_SUPER_GRAVITRON)), 220 - (help.glow), 220 - (help.glow), 255 - (help.glow / 2));

                std::string tempstring = help.timestring(game.swnrecord);
                font::print(PR_BOR | PR_CEN, -1, 190, loc::gettext(STR_ID("Best Time", STR_BEST_TIME)), 220 - (help.glow), 220 - (help.glow), 255 - (help.glow / 2));
                font::print(PR_2X | PR_BOR | PR_CEN | PR_CJK_LOW, -1, 205, tempstring, 220 - (help.glow), 220 - (help.glow), 255 - (help.glow / 2));
            }
            else if (int(game.swndelay / 10) % 2 == 1)
            {
                font::print(PR_2X | PR_BOR | PR_CEN, -1, 20, loc::gettext(STR_ID("SUPER GRAVITRON", STR_SUPER_GRAVITRON)), 220 - (help.glow), 220 - (help.glow), 255 - (help.glow / 2));
                font::print(PR_3X | PR_BOR | PR_CEN, -1, 200, loc::gettext(STR_ID("GO!", STR_GO_CAP)), 220 - (help.glow), 220 - (help.glow), 255 - (help.glow / 2));
            }
        }
    }

    if (game.intimetrial && graphics.fademode == FADE_NONE)
    {
        //Draw countdown!
        if (game.timetrialcountdown > 0)
        {
            if (game.timetrialcountdown < 30)
            {
                if (int(game.timetrialcountdown / 4) % 2 == 0)
                {
                    font::print(PR_4X | PR_CEN | PR_BOR, -1, 100, loc::gettext(STR_ID("Go!", STR_GO)), 220 - (help.glow), 220 - (help.glow), 255 - (help.glow / 2));
                }
            }
            else if (game.timetrialcountdown < 60)
            {
                font::print(PR_4X | PR_CEN | PR_BOR, -1, 100, "1", 220 - (help.glow), 220 - (help.glow), 255 - (help.glow / 2));
            }
            else if (game.timetrialcountdown < 90)
            {
                font::print(PR_4X | PR_CEN | PR_BOR,  -1, 100, "2", 220 - (help.glow), 220 - (help.glow), 255 - (help.glow / 2));
            }
            else if (game.timetrialcountdown < 120)
            {
                font::print(PR_4X | PR_CEN | PR_BOR,  -1, 100, "3", 220 - (help.glow), 220 - (help.glow), 255 - (help.glow / 2));
            }
        }
        else if (!roomname_translator::is_pausing() && !game.translator_exploring)
        {
            char buffer[SCREEN_WIDTH_CHARS + 1];
            game.timestringcenti(buffer, sizeof(buffer));

            //Draw OSD stuff
            const char* tempstring = loc::gettext(STR_ID("TIME:", STR_TRIAL_TIME));
            int label_len = font::len(0, tempstring);
            font::print(PR_BOR | PR_RTL_XFLIP, 6, 18, tempstring,  255,255,255);
            tempstring = loc::gettext(STR_ID("DEATH:", STR_TRIAL_DEATH));
            label_len = SDL_max(label_len, font::len(0, tempstring));
            font::print(PR_BOR | PR_RTL_XFLIP, 6, 30, tempstring,  255,255,255);
            tempstring = loc::gettext(STR_ID("SHINY:", STR_TRIAL_SHINY));
            label_len = SDL_max(label_len, font::len(0, tempstring));
            font::print(PR_BOR | PR_RTL_XFLIP, 6, 42, tempstring,  255,255,255);

            if(game.timetrialparlost)
            {
                font::print(PR_BOR | PR_RTL_XFLIP, 8+label_len, 18, buffer,  196, 80, 80);
            }
            else
            {
                font::print(PR_BOR | PR_RTL_XFLIP, 8+label_len, 18, buffer,  196, 196, 196);
            }
            if(game.deathcounts>0)
            {
                font::print(PR_BOR | PR_RTL_XFLIP, 8+label_len, 30,help.String(game.deathcounts),  196, 80, 80);
            }
            else
            {
                font::print(PR_BOR | PR_RTL_XFLIP, 8+label_len, 30,help.String(game.deathcounts),  196, 196, 196);
            }
            vformat_buf(
                buffer, sizeof(buffer),
                loc::gettext(STR_ID("{n_trinkets} of {max_trinkets}", STR_TOTAL_TRINKETS_OF)),
                "n_trinkets:int, max_trinkets:int",
                game.trinkets(), game.timetrialshinytarget
            );
            if(game.trinkets()<game.timetrialshinytarget)
            {
                font::print(PR_BOR | PR_RTL_XFLIP, 8+label_len, 42, buffer,  196, 80, 80);
            }
            else
            {
                font::print(PR_BOR | PR_RTL_XFLIP, 8+label_len, 42, buffer,  196, 196, 196);
            }

            std::string time = game.timetstring(game.timetrialpar);
            label_len = font::len(0, time.c_str());
            if(game.timetrialparlost)
            {
                font::print(PR_BOR | PR_RTL_XFLIP | PR_RIGHT, 307-label_len-8, 214, loc::gettext(STR_ID("PAR TIME:", STR_TRIAL_PAR_TIME)),  80, 80, 80);
                font::print(PR_BOR | PR_RTL_XFLIP,            307-label_len,   214, time,  80, 80, 80);
            }
            else
            {
                font::print(PR_BOR | PR_RTL_XFLIP | PR_RIGHT, 307-label_len-8, 214, loc::gettext(STR_ID("PAR TIME:", STR_TRIAL_PAR_TIME)),  255, 255, 255);
                font::print(PR_BOR | PR_RTL_XFLIP,            307-label_len,   214, time,  196, 196, 196);
            }
        }
    }

    float act_alpha = graphics.lerp(game.prev_act_fade, game.act_fade) / 10.0f;
    if(game.act_fade>5 || game.prev_act_fade>5)
    {
        const char* prompt = game.activity_lastprompt.c_str();
        #ifndef __NDS__ // should already be localized
        if (game.activity_gettext)
        {
            prompt = loc::gettext(prompt);
        }
        #endif
        char buffer[SCREEN_WIDTH_CHARS + 1];
        const char* final_string = interact_prompt(
            buffer,
            sizeof(buffer),
            prompt
        );

        uint8_t text_r, text_g, text_b;
        uint32_t text_flags = (game.activity_gettext ? PR_FONT_INTERFACE : PR_FONT_LEVEL)
        | PR_BRIGHTNESS(act_alpha*255) | PR_CJK_LOW | PR_CEN;

        if (game.activity_r == 0 && game.activity_g == 0 && game.activity_b == 0)
        {
            text_r = 196;
            text_g = 196;
            text_b = 255 - help.glow;
        }
        else
        {
            short lines;
            font::string_wordwrap(text_flags, final_string, 37*8, &lines);

            graphics.drawpixeltextbox(
                4,
                game.activity_y + 4,
                39*8,
                16 + font::height(text_flags)*lines,
                game.activity_r*act_alpha,
                game.activity_g*act_alpha,
                game.activity_b*act_alpha
            );

            text_r = game.activity_r;
            text_g = game.activity_g;
            text_b = game.activity_b;
        }

        font::print_wrap(
            text_flags,
            -1,
            game.activity_y + 12,
            final_string,
            text_r,
            text_g,
            text_b,
            8,
            37*8
        );
    }

    if (obj.trophytext > 0 || obj.oldtrophytext > 0)
    {
        graphics.drawtrophytext();
    }

    level_debugger::render();

    graphics.renderwithscreeneffects();


    #ifdef __NDS__
    rendermap_sub(true);
    #endif
}

static void draw_roomname_menu(void)
{
    const char* name;

    if (map.hiddenname[0] != '\0')
    {
        name = loc::gettext_roomname_special(map.hiddenname);
    }
    else
    {
        name = loc::gettext_roomname(map.custommode, game.roomx, game.roomy, map.roomname, map.roomname_special);
    }

    font::print(PR_FONT_LEVEL | PR_CEN, -1, 2, name, 196, 196, 255 - help.glow);
}

/* Used to keep some graphics positions on the map screen
 * the same in Flip Mode. */
#define FLIP(y, h) (graphics.flipmode ? 220 - (y) - (h) : (y))
#define FLIP_PR_CJK_LOW (graphics.flipmode ? PR_CJK_HIGH : PR_CJK_LOW)
#define FLIP_PR_CJK_HIGH (graphics.flipmode ? PR_CJK_LOW : PR_CJK_HIGH)

static MapRenderData getmaprenderdata(void)
{
    MapRenderData data;

    data.zoom = map.custommode ? map.customzoom : 1;
    data.xoff = map.custommode ? map.custommmxoff : 0;
    data.yoff = map.custommode ? map.custommmyoff : 0;
    data.legendxoff = 40 + data.xoff;
    data.legendyoff = 21 + data.yoff;

    // Magic numbers for centering legend tiles.
    switch (data.zoom)
    {
    case 4:
        data.legendxoff += 20;
        data.legendyoff += 14;
        break;
    case 2:
        data.legendxoff += 8;
        data.legendyoff += 5;
        break;
    default:
        data.legendxoff += 2;
        data.legendyoff += 1;
        break;
    }

    return data;
}

static void rendermap(void)
{
    if (map.custommode && map.customshowmm)
    {
        graphics.drawpixeltextbox(35 + map.custommmxoff, 16 + map.custommmyoff, map.custommmxsize + 10, map.custommmysize + 10, 65, 185, 207);
        graphics.drawpartimage(graphics.minimap_mounted ? IMAGE_MINIMAP : IMAGE_CUSTOMMINIMAP, 40 + map.custommmxoff, 21 + map.custommmyoff, map.custommmxsize, map.custommmysize);
        return;
     }

    graphics.drawpixeltextbox(35, 16, 250, 190, 65, 185, 207);
    graphics.drawimage(IMAGE_MINIMAP, 40, 21, false);
}

static void rendermapfog(void)
{
    const MapRenderData data = getmaprenderdata();

    for (int j = 0; j < map.getheight(); j++)
    {
        for (int i = 0; i < map.getwidth(); i++)
        {
            if (!map.isexplored(i, j))
            {
                // Draw the fog, depending on the custom zoom size
                for (int x = 0; x < data.zoom; x++)
                {
                    for (int y = 0; y < data.zoom; y++)
                    {
                        graphics.drawimage(IMAGE_COVERED, data.xoff + 40 + (x * 12) + (i * (12 * data.zoom)), data.yoff + 21 + (y * 9) + (j * (9 * data.zoom)), false);
                    }
                }
            }
        }
    }
}

static void rendermaplegend(void)
{
    // Draw the map legend, aka teleports/targets/trinkets

    const MapRenderData data = getmaprenderdata();

    for (size_t i = 0; i < map.teleporters.size(); i++)
    {
        if (map.showteleporters && map.isexplored(map.teleporters[i].x, map.teleporters[i].y))
        {
            font::print(PR_FONT_8X8 | PR_FULLBOR, data.legendxoff + (map.teleporters[i].x * 12 * data.zoom), data.legendyoff + (map.teleporters[i].y * 9 * data.zoom), "💿", 171, 255, 252);
        }
        else if (map.showtargets && !map.isexplored(map.teleporters[i].x, map.teleporters[i].y))
        {
            font::print(PR_FONT_8X8 | PR_FULLBOR, data.legendxoff + (map.teleporters[i].x * 12 * data.zoom), data.legendyoff + (map.teleporters[i].y * 9 * data.zoom), "❓", 64, 64, 64);
        }
    }

    if (map.showtrinkets)
    {
        for (size_t i = 0; i < map.shinytrinkets.size(); i++)
        {
            if (!obj.collect[i])
            {
                font::print(PR_FONT_8X8 | PR_FULLBOR, data.legendxoff + (map.shinytrinkets[i].x * 12 * data.zoom), data.legendyoff + (map.shinytrinkets[i].y * 9 * data.zoom), "🪙", 254, 252, 58);
            }
        }
    }
}

static void rendermapcursor(const bool flashing)
{
    const MapRenderData data = getmaprenderdata();

    if (!map.custommode && game.roomx == 109)
    {
        // Draw the tower specially
        if (!flashing || game.noflashingmode)
        {
            graphics.draw_rect(40 + ((game.roomx - 100) * 12) + 2, 21 + 2, 12 - 4, 180 - 4, 16, 245 - (help.glow * 2), 245 - (help.glow * 2));
        }
        else if (map.cursorstate == 1)
        {
            if (int(map.cursordelay / 4) % 2 == 0)
            {
                graphics.draw_rect(40 + ((game.roomx - 100) * 12), 21, 12, 180, 255, 255, 255);
                graphics.draw_rect(40 + ((game.roomx - 100) * 12) + 2, 21 + 2, 12 - 4, 180 - 4, 255, 255, 255);
            }
        }
        else if (map.cursorstate == 2 && (int(map.cursordelay / 15) % 2 == 0))
        {
            graphics.draw_rect(40 + ((game.roomx - 100) * 12) + 2, 21 + 2, 12 - 4, 180 - 4, 16, 245 - (help.glow), 245 - (help.glow));
        }
        return;
    }

    if (!flashing || ((map.cursorstate == 2 && int(map.cursordelay / 15) % 2 == 0) || game.noflashingmode))
    {
        int margin = (data.zoom == 4) ? 2 : 1;
        graphics.draw_rect(
            40 + ((game.roomx - 100) * 12 * data.zoom) + margin + data.xoff,
            21 + ((game.roomy - 100) * 9 * data.zoom) + margin + data.yoff,
            (12 * data.zoom) - (2 * margin), (9 * data.zoom) - (2 * margin),
            16, 245 - (help.glow), 245 - (help.glow)
        );
    }
    else if (map.cursorstate == 1 && int(map.cursordelay / 4) % 2 == 0)
    {
        graphics.draw_rect(40 + ((game.roomx - 100) * 12 * data.zoom) + data.xoff, 21 + ((game.roomy - 100) * 9 * data.zoom) + data.yoff, 12 * data.zoom, 9 * data.zoom, 255, 255, 255);
        graphics.draw_rect(40 + ((game.roomx - 100) * 12 * data.zoom) + 2 + data.xoff, 21 + ((game.roomy - 100) * 9 * data.zoom) + 2 + data.yoff, (12 * data.zoom) - 4, (9 * data.zoom) - 4, 255, 255, 255);
    }
}

void maprender(void)
{
    #ifdef __NDS__
    if (graphics.menuoffset > 0) {
        graphics.lerp_freeze = true;
        if (map.towermode)
        {
            if (!graphics.backgrounddrawn)
            {
                if (game.colourblindmode)
                {
                    graphics.clear_tile_layer(true);
                }
                else
                {
                    graphics.drawtowerbackground(graphics.towerbg);
                }
            }
            if (!graphics.foregrounddrawn)
            {
                graphics.drawtowermap();
            }
        }
        else
        {
            if (!graphics.backgrounddrawn)
            {
                if (game.colourblindmode)
                {
                    graphics.clear_tile_layer(true);
                }
                else
                {
                    graphics.drawbackground(map.background);
                }
            }
            if (!graphics.foregrounddrawn)
            {
                if ((map.finalmode || map.custommode) && map.final_colormode)
                {
                    graphics.drawfinalmap();
                }
                else
                {
                    graphics.drawmap();
                }
            }
        }
        graphics.drawentities();
        if (map.towermode)
        {
            graphics.drawtowerspikes();
        }
        graphics.lerp_freeze = false;
    }
    graphics.scroll_gl(0, graphics.lerp(graphics.oldmenuoffset, graphics.menuoffset));
    graphics.fill_rect(0, 0, 320, 12, 0, 0, 0);
    #else
    graphics.set_render_target(graphics.menuTexture);
    graphics.clear();
    #endif

    draw_roomname_menu();

    //Background color
    graphics.fill_rect(0, 12, 320, 240, 10, 24, 26 );

    //Menubar:
    graphics.drawpixeltextbox( -10, 212, 43*8, 16 + font::height(PR_FONT_INTERFACE), 65, 185, 207);

    // Draw the selected page name at the bottom
    // menupage 0 - 3 is the pause screen
    if (script.running && game.menupage == 3)
    {
        // While in a cutscene, you can only save
        char buffer[SCREEN_WIDTH_CHARS + 1];
        vformat_buf(buffer, sizeof(buffer), loc::get_langmeta()->menu_select_tight.c_str(), "label:str", loc::gettext(STR_ID("SAVE", STR_SAVE)));
        font::print(PR_CEN | PR_CJK_LOW, -1, 220, buffer, 196, 196, 255 - help.glow);
    }
    else if (game.menupage <= 3)
    {
        const char* tab1;
        if (game.insecretlab)
        {
            tab1 = loc::gettext(STR_ID("GRAV", STR_GRAV));
        }
        else if (obj.flags[67] && !map.custommode)
        {
            tab1 = loc::gettext(STR_ID("SHIP", STR_SHIP));
        }
        else
        {
            tab1 = loc::gettext(STR_ID("CREW", STR_CREW));
        }
#define TAB(opt, text) graphics.map_tab(opt, text, game.menupage == opt)
    #ifndef __NDS__
        TAB(0, loc::gettext(STR_ID("MAP", STR_MAP));)
    #endif
        TAB(1, tab1);
        TAB(2, loc::gettext(STR_ID("STATS", STR_STATS)));
        TAB(3, loc::gettext(STR_ID("SAVE", STR_SAVE)));
#undef TAB
    }

    // Draw menu header
    switch (game.menupage)
    {
    case 30:
    case 31:
    case 32:
    case 33:
        font::print(PR_CEN | PR_CJK_LOW, -1, 220, loc::gettext(STR_ID("[ PAUSE ]", STR_IGM_PAUSE)), 196, 196, 255 - help.glow);
    }

    // Draw menu options
    if (game.menupage >= 30 && game.menupage <= 33)
    {
#define OPTION(opt, text) graphics.map_option(opt, 4, text, game.menupage - 30 == opt)
        OPTION(0, loc::gettext(STR_ID("return to game", STR_RETURN_TO_GAME)));
        OPTION(1, loc::gettext(STR_ID("options", STR_OPTIONS)));
        OPTION(2, loc::gettext(STR_ID("quit to menu", STR_QUIT_TO_MENU)));
#undef OPTION
    }

    /* FIXME: about the code below where this is used (case 10/11/20/21)... I've seen better code.
     * We should rewrite it to use graphics::map_option, but until then... */
    int selection_offset;
    {
        char buffer[SCREEN_WIDTH_CHARS + 1];
        vformat_buf(buffer, sizeof(buffer), loc::get_langmeta()->menu_select.c_str(), "label:str", "");
        selection_offset = font::len(0, buffer) / 2;
    }

    // Draw the actual menu
    switch(game.menupage)
    {
    case 0:
        #ifdef __NDS__
        game.menupage = 1;
        [[fallthrough]]; 
        #else
        rendermap();

        if (map.finalmode || (map.custommode&&!map.customshowmm))
        {
            // Cover the whole map
            for (int j = 0; j < 20; j++)
            {
                for (int i = 0; i < 20; i++)
                {
                    graphics.drawimage(IMAGE_COVERED, 40 + (i * 12), 21 + (j * 9), false);
                }
            }
            font::print(PR_CEN | PR_BOR, -1, 105, loc::gettext(STR_ID("NO SIGNAL", STR_NO_SIGNAL)), 245, 245, 245);
        }
        else
        {
            rendermapfog();
            rendermapcursor(true);
            rendermaplegend();
        }
        break;
        #endif
    case 1:
        if (game.insecretlab)
        {
            if (graphics.flipmode)
            {
                font::print_wrap(PR_CEN, -1, 174, loc::gettext(STR_ID("SUPER GRAVITRON HIGHSCORE", STR_SUPER_GRAVITRON_HIGHSCORE)), 196, 196, 255 - help.glow);

                std::string tempstring = help.timestring(game.swnrecord);
                font::print(PR_CEN, -1, 124, loc::gettext(STR_ID("Best Time", STR_BEST_TIME)), 196, 196, 255 - help.glow);
                font::print(PR_2X | PR_CEN | PR_CJK_HIGH, -1, 102, tempstring, 196, 196, 255 - help.glow);

                switch(game.swnbestrank)
                {
                case 0:
                    font::print_wrap(PR_CEN, -1, 40, loc::gettext(STR_ID("Next Trophy at 5 seconds", STR_NEXT_TROPHY_5_SECONDS)), 196, 196, 255 - help.glow);
                    break;
                case 1:
                    font::print_wrap(PR_CEN, -1, 40, loc::gettext(STR_ID("Next Trophy at 10 seconds", STR_NEXT_TROPHY_10_SECONDS)), 196, 196, 255 - help.glow);
                    break;
                case 2:
                    font::print_wrap(PR_CEN, -1, 40, loc::gettext(STR_ID("Next Trophy at 15 seconds", STR_NEXT_TROPHY_15_SECONDS)), 196, 196, 255 - help.glow);
                    break;
                case 3:
                    font::print_wrap(PR_CEN, -1, 40, loc::gettext(STR_ID("Next Trophy at 20 seconds", STR_NEXT_TROPHY_20_SECONDS)), 196, 196, 255 - help.glow);
                    break;
                case 4:
                    font::print_wrap(PR_CEN, -1, 40, loc::gettext(STR_ID("Next Trophy at 30 seconds", STR_NEXT_TROPHY_30_SECONDS)), 196, 196, 255 - help.glow);
                    break;
                case 5:
                    font::print_wrap(PR_CEN, -1, 40, loc::gettext(STR_ID("Next Trophy at 1 minute", STR_NEXT_TROPHY_1_MINUTE)), 196, 196, 255 - help.glow);
                    break;
                case 6:
                    font::print_wrap(PR_CEN, -1, 40, loc::gettext(STR_ID("All Trophies collected!", STR_GOT_ALL_TROPHIES)), 196, 196, 255 - help.glow);
                    break;
                }
            }
            else
            {
                font::print_wrap(PR_CEN, -1, 40, loc::gettext(STR_ID("SUPER GRAVITRON HIGHSCORE", STR_SUPER_GRAVITRON_HIGHSCORE)), 196, 196, 255 - help.glow);

                std::string tempstring = help.timestring(game.swnrecord);
                font::print(PR_CEN, -1, 90, loc::gettext(STR_ID("Best Time", STR_BEST_TIME)), 196, 196, 255 - help.glow);
                font::print(PR_2X | PR_CEN | PR_CJK_LOW, -1, 104, tempstring, 196, 196, 255 - help.glow);

                switch(game.swnbestrank)
                {
                case 0:
                    font::print_wrap(PR_CEN, -1, 174, loc::gettext(STR_ID("Next Trophy at 5 seconds", STR_NEXT_TROPHY_5_SECONDS)), 196, 196, 255 - help.glow);
                    break;
                case 1:
                    font::print_wrap(PR_CEN, -1, 174, loc::gettext(STR_ID("Next Trophy at 10 seconds", STR_NEXT_TROPHY_10_SECONDS)), 196, 196, 255 - help.glow);
                    break;
                case 2:
                    font::print_wrap(PR_CEN, -1, 174, loc::gettext(STR_ID("Next Trophy at 15 seconds", STR_NEXT_TROPHY_15_SECONDS)), 196, 196, 255 - help.glow);
                    break;
                case 3:
                    font::print_wrap(PR_CEN, -1, 174, loc::gettext(STR_ID("Next Trophy at 20 seconds", STR_NEXT_TROPHY_20_SECONDS)), 196, 196, 255 - help.glow);
                    break;
                case 4:
                    font::print_wrap(PR_CEN, -1, 174, loc::gettext(STR_ID("Next Trophy at 30 seconds", STR_NEXT_TROPHY_30_SECONDS)), 196, 196, 255 - help.glow);
                    break;
                case 5:
                    font::print_wrap(PR_CEN, -1, 174, loc::gettext(STR_ID("Next Trophy at 1 minute", STR_NEXT_TROPHY_1_MINUTE)), 196, 196, 255 - help.glow);
                    break;
                case 6:
                    font::print_wrap(PR_CEN, -1, 174, loc::gettext(STR_ID("All Trophies collected!", STR_GOT_ALL_TROPHIES)), 196, 196, 255 - help.glow);
                    break;
                }
            }
        }
        else if (obj.flags[67] && !map.custommode)
        {
            char buffer[SCREEN_WIDTH_CHARS + 1];
            vformat_buf(
                buffer, sizeof(buffer),
                loc::gettext(STR_ID("Press {button} to warp to the ship.", STR_PROMPT_WARP_SHIP)),
                "button:but",
                vformat_button(ActionSet_InGame, Action_InGame_ACTION)
            );
            font::print_wrap(PR_CEN, -1, 105, buffer, 196, 196, 255 - help.glow);
        }
        else if(map.custommode){
            LevelMetaData& meta = cl.ListOfMetaData[game.playcustomlevel];

            uint32_t title_flags = meta.title_is_gettext ? PR_FONT_INTERFACE : PR_FONT_LEVEL;
            uint32_t creator_flags = meta.creator_is_gettext ? PR_FONT_INTERFACE : PR_FONT_LEVEL;

            font::print(title_flags | PR_2X | PR_CEN, -1, FLIP(45, 8), meta.title, 196, 196, 255 - help.glow);
            int sp = SDL_max(10, font::height(PR_FONT_LEVEL));
            graphics.print_level_creator(creator_flags, FLIP(70, 8), meta.creator, 196, 196, 255 - help.glow);
            font::print(PR_FONT_LEVEL | PR_CEN, -1, FLIP(70+sp, 8), meta.website, 196, 196, 255 - help.glow);
            font::print(PR_FONT_LEVEL | PR_CEN, -1, FLIP(70+sp*3, 8), meta.Desc1, 196, 196, 255 - help.glow);
            font::print(PR_FONT_LEVEL | PR_CEN, -1, FLIP(70+sp*4, 8), meta.Desc2, 196, 196, 255 - help.glow);
            if (sp <= 10)
            {
                font::print(PR_FONT_LEVEL | PR_CEN, -1, FLIP(70+sp*5, 8), meta.Desc3, 196, 196, 255 - help.glow);
            }

            int remaining = cl.numcrewmates() - game.crewmates();

            char buffer[SCREEN_WIDTH_CHARS + 1];
            loc::gettext_plural_fill(
                buffer, sizeof(buffer),
                "{n_crew|wordy} crewmates remain",
                "{n_crew|wordy} crewmate remains",
                "n_crew:int",
                remaining
            );
            font::print_wrap(PR_CEN, -1, FLIP(165, 8), buffer, 196, 196, 255 - help.glow);
        }
        else
        {
            if (graphics.flipmode)
            {
                for (int i = 0; i < 3; i++)
                {
                    graphics.drawcrewman(16, 32 + (i * 64), 2-i, game.crewstats[2-i]);
                    if (game.crewstats[(2-i)])
                    {
                        graphics.printcrewname(44, 32 + (i * 64)+4+10, 2-i);
                    }
                    else
                    {
                        graphics.printcrewnamedark(44, 32 + (i * 64)+4+10, 2-i);
                    }
                    graphics.printcrewnamestatus(44, 32 + (i * 64)+4, 2-i, game.crewstats[(2-i)]);

                    graphics.drawcrewman(16+160, 32 + (i * 64), (2-i)+3, game.crewstats[(2-i)+3]);
                    if (game.crewstats[(2-i)+3])
                    {
                        graphics.printcrewname(44+160, 32 + (i * 64)+4+10, (2-i)+3);
                    }
                    else
                    {
                        graphics.printcrewnamedark(44+160, 32 + (i * 64)+4+10, (2-i)+3);
                    }
                    graphics.printcrewnamestatus(44+160, 32 + (i * 64)+4, (2-i)+3, game.crewstats[(2-i)+3]);
                }
            }
            else
            {
                for (int i = 0; i < 3; i++)
                {
                    graphics.drawcrewman(16, 32 + (i * 64), i, game.crewstats[i]);
                    if (game.crewstats[i])
                    {
                        graphics.printcrewname(44, 32 + (i * 64)+4, i);
                    }
                    else
                    {
                        graphics.printcrewnamedark(44, 32 + (i * 64)+4, i);
                    }
                    graphics.printcrewnamestatus(44, 32 + (i * 64)+4+10, i, game.crewstats[i]);

                    graphics.drawcrewman(16+160, 32 + (i * 64), i+3, game.crewstats[i+3]);
                    if (game.crewstats[i+3])
                    {
                        graphics.printcrewname(44+160, 32 + (i * 64)+4, i+3);
                    }
                    else
                    {
                        graphics.printcrewnamedark(44+160, 32 + (i * 64)+4, i+3);
                    }
                    graphics.printcrewnamestatus(44+160, 32 + (i * 64)+4+10, i+3, game.crewstats[i+3]);
                }
            }
        }
        break;
    case 2:
    {
        int max_trinkets;
        if (map.custommode)
        {
            max_trinkets = cl.numtrinkets();
        }
        else
        {
            max_trinkets = 20;
        }

        /* Stats. */
        font::print(PR_CEN | FLIP_PR_CJK_HIGH, -1, FLIP(52, 8), loc::gettext(STR_ID("[Trinkets found]", STR_MM_TRINKETS_FOUND)), 196, 196, 255 - help.glow);
        char buffer[SCREEN_WIDTH_CHARS + 1];
        vformat_buf(
            buffer, sizeof(buffer),
            loc::gettext(STR_ID("{n_trinkets|wordy} out of {max_trinkets|wordy}", STR_TOTAL_TRINKETS_WORDY)),
            "n_trinkets:int, max_trinkets:int",
            game.trinkets(), max_trinkets
        );
        font::print(PR_CEN | FLIP_PR_CJK_LOW, -1, FLIP(64, 8), buffer, 96, 96, 96);

        font::print(PR_CEN | FLIP_PR_CJK_HIGH, -1, FLIP(102, 8), loc::gettext(STR_ID("[Number of Deaths]", STR_MM_NUM_DEATHS)), 196, 196, 255 - help.glow);
        font::print(PR_CEN | FLIP_PR_CJK_LOW, -1, FLIP(114, 8), help.String(game.deathcounts), 96, 96, 96);

        font::print(PR_CEN | FLIP_PR_CJK_HIGH, -1, FLIP(152, 8), loc::gettext(STR_ID("[Time Taken]", STR_MM_TIME_TAKEN)), 196, 196, 255 - help.glow);
        font::print(PR_CEN | FLIP_PR_CJK_LOW, -1, FLIP(164, 8), game.timestring(), 96, 96, 96);
        break;
    }
    case 3:
    {
        if (game.inintermission || game.translator_exploring)
        {
            font::print_wrap(PR_CEN, -1, 115, loc::gettext(STR_ID("Cannot Save in Level Replay", STR_CANT_SAVE_IN_REPLAY)), 146, 146, 180);
            break;
        }
        if (game.nodeathmode)
        {
            font::print_wrap(PR_CEN, -1, 115, loc::gettext(STR_ID("Cannot Save in No Death Mode", STR_CANT_SAVE_IN_NO_DEATH)), 146, 146, 180);
            break;
        }
        if (game.intimetrial)
        {
            font::print_wrap(PR_CEN, -1, 115, loc::gettext(STR_ID("How'd you get here?", STR_HOWD_YOU_GET_HERE)), 146, 146, 180);
            break;
        }
        if (game.insecretlab)
        {
            font::print_wrap(PR_CEN, -1, 115, loc::gettext(STR_ID("Cannot Save in Secret Lab", STR_CANT_SAVE_IN_SECRET_LAB)), 146, 146, 180);
            break;
        }
        if (game.gamesavefailed)
        {
            font::print_wrap(PR_CEN, -1, 115, loc::gettext(STR_ID("ERROR: Could not save game!", STR_ERR_SAVE_GAME)), 146, 146, 180);
            break;
        }

        /* We are not in a special case, so draw the save screen now... */

        if (!map.custommode)
        {
            /* FIXME: The text here should be automatically "balance-wrapped" instead of hardcoding the width.
             * In fact, maybe print_wrap should balance-wrap by default. */
            font::print_wrap(PR_CEN, -1, 174, loc::gettext(STR_ID("(Note: The game is autosaved at every teleporter.)", STR_NOTE_AUTOSAVE)), 146, 146, 180, 12);
        }

        if (!game.gamesaved)
        {
            char buffer[SCREEN_WIDTH_CHARS + 1];
            vformat_buf(
                buffer, sizeof(buffer),
                loc::gettext(STR_ID("[Press {button} to save your game]", STR_PROMPT_SAVE)),
                "button:but",
                vformat_button(ActionSet_InGame, Action_InGame_ACTION)
            );

            font::print(PR_CEN, -1, 80, buffer, 255 - help.glow*2, 255 - help.glow*2, 255 - help.glow);

            if (map.custommode || !game.last_quicksave.exists)
            {
                break;
            }

            font::print(PR_CEN, -1, FLIP(100, 8), loc::gettext(STR_ID("Last Save:", STR_LAST_SAVE)), 164 - help.glow/4, 164 - help.glow/4, 164);

            struct Game::Summary* last = &game.last_quicksave;
            vformat_buf(
                buffer, sizeof(buffer),
                loc::gettext(STR_ID("{area}, {time}", STR_AREA_TIME)),
                "area:str, time:str",
                loc::gettext_roomname_special(map.currentarea(last->saverx, last->savery)),
                game.giventimestring(last->hours, last->minutes, last->seconds).c_str()
            );

            font::print(PR_CEN, -1, FLIP(112, 8), buffer, 164 - help.glow/4, 164 - help.glow/4, 164);
            break;
        }

        /* We are only still here if the game has been quicksaved... */

        font::print_wrap(PR_CEN, -1, 36, loc::gettext(STR_ID("Game saved ok!", STR_SAVED_OK)), 255 - help.glow/2, 255 - help.glow/2, 255 - help.glow/2);

        graphics.drawpixeltextbox(17, 65, 286, 90, 65, 185, 207);

        if (map.custommode)
        {
            font::print(PR_CEN | PR_FONT_LEVEL, -1, FLIP(90, 8), game.customleveltitle, 25, 255 - help.glow/2, 255 - help.glow/2);
        }
        else
        {
            size_t i;
            font::print(
                PR_CEN, -1, FLIP(80, 8),
                loc::gettext_roomname_special(map.currentarea(game.last_quicksave.saverx, game.last_quicksave.savery)),
                25, 255 - help.glow/2, 255 - help.glow/2
            );
            for (i = 0; i < SDL_arraysize(game.crewstats); ++i)
            {
                /* Crewmates are annoying. Their height is 21 pixels, but to flip them,
                 * we also have to account for their 2-pixel y-offset (and multiply it by 2). */
                graphics.drawcrewman(169 - 3*42 + i*42, FLIP(95, 21 + 2*2), i, game.crewstats[i], true);
            }
        }

        font::print(0, 59, FLIP(132, 8), game.savetime, 255 - help.glow/2, 255 - help.glow/2, 255 - help.glow/2);
        char buffer[SCREEN_WIDTH_CHARS + 1];
        vformat_buf(buffer, sizeof(buffer),
            loc::gettext(STR_ID("{savebox_n_trinkets|wordy}", STR_SAVEBOX_TRINKETS_WORDY)),
            "savebox_n_trinkets:int",
            game.savetrinkets
        );
        font::print(PR_RIGHT, 262, FLIP(132, 8), buffer, 255 - help.glow/2, 255 - help.glow/2, 255 - help.glow/2);

        if (graphics.flipmode)
        {
            graphics.draw_flipsprite(34, FLIP(126, 17), 50, graphics.col_clock);
            graphics.draw_flipsprite(270, FLIP(126, 17), 22, graphics.col_trinket);
        }
        else
        {
            graphics.draw_sprite(34, FLIP(126, 17), 50, graphics.col_clock);
            graphics.draw_sprite(270, FLIP(126, 17), 22, graphics.col_trinket);
        }
        break;
    }
    case 10:
        font::print(PR_CEN | PR_CJK_LOW, -1, 220, loc::gettext(STR_ID("[ QUIT ]", STR_IGM_QUIT)), 196, 196, 255 - help.glow);

        if (graphics.flipmode)
        {
            if (game.inspecial())
            {
                font::print_wrap(PR_CEN, -1, 135, loc::gettext(STR_ID("Return to main menu?", STR_WANNA_RETURN_TO_MAIN)), 196, 196, 255 - help.glow, 12);
            }
            else
            {
                font::print_wrap(PR_CEN, -1, 142, loc::gettext(STR_ID("Do you want to quit? You will lose any unsaved progress.", STR_WANNA_QUIT_UNSAVED)), 196, 196, 255 - help.glow, 12);
            }

            font::print(PR_RTL_XFLIP, 80-selection_offset, 88, loc::gettext(STR_ID("[ NO, KEEP PLAYING ]", STR_NO_KEEP_PLAYING_HOVER)), 196, 196, 255 - help.glow);
            font::print(PR_RTL_XFLIP, 80 + 32, 76, loc::gettext(STR_ID("yes, quit to menu", STR_YES_QUIT_TO_MENU)),  96, 96, 96);
        }
        else
        {

            if (game.inspecial())
            {
                font::print_wrap(PR_CEN, -1, 80, loc::gettext(STR_ID("Return to main menu?", STR_WANNA_RETURN_TO_MAIN)), 196, 196, 255 - help.glow, 12);
            }
            else
            {
                font::print_wrap(PR_CEN, -1, 76, loc::gettext(STR_ID("Do you want to quit? You will lose any unsaved progress.", STR_WANNA_QUIT_UNSAVED)), 196, 196, 255 - help.glow, 12);
            }

            font::print(PR_RTL_XFLIP, 80-selection_offset, 130, loc::gettext(STR_ID("[ NO, KEEP PLAYING ]", STR_NO_KEEP_PLAYING_HOVER)), 196, 196, 255 - help.glow);
            font::print(PR_RTL_XFLIP, 80 + 32, 142, loc::gettext(STR_ID("yes, quit to menu", STR_YES_QUIT_TO_MENU)),  96, 96, 96);

        }
        break;
    case 11:
        font::print(PR_CEN | PR_CJK_LOW, -1, 220, loc::gettext(STR_ID("[ QUIT ]", STR_IGM_QUIT)), 196, 196, 255 - help.glow);

        if (graphics.flipmode)
        {
            if (game.inspecial())
            {
                font::print_wrap(PR_CEN, -1, 135, loc::gettext(STR_ID("Return to main menu?", STR_WANNA_RETURN_TO_MAIN)), 196, 196, 255 - help.glow, 12);
            }
            else
            {
                font::print_wrap(PR_CEN, -1, 142, loc::gettext(STR_ID("Do you want to quit? You will lose any unsaved progress.", STR_WANNA_QUIT_UNSAVED)), 196, 196, 255 - help.glow, 12);
            }

            font::print(PR_RTL_XFLIP, 80, 88, loc::gettext(STR_ID("no, keep playing", STR_NO_KEEP_PLAYING)), 96,96,96);
            font::print(PR_RTL_XFLIP, 80+32-selection_offset, 76, loc::gettext(STR_ID("[ YES, QUIT TO MENU ]", STR_YES_QUIT_TO_MENU_HOVER)),  196, 196, 255 - help.glow);
        }
        else
        {
            if (game.inspecial())
            {
                font::print_wrap(PR_CEN, -1, 80, loc::gettext(STR_ID("Return to main menu?", STR_WANNA_RETURN_TO_MAIN)), 196, 196, 255 - help.glow, 12);
            }
            else
            {
                font::print_wrap(PR_CEN, -1, 76, loc::gettext(STR_ID("Do you want to quit? You will lose any unsaved progress.", STR_WANNA_QUIT_UNSAVED)), 196, 196, 255 - help.glow, 12);
            }

            font::print(PR_RTL_XFLIP, 80, 130, loc::gettext(STR_ID("no, keep playing", STR_NO_KEEP_PLAYING)), 96,96,96);
            font::print(PR_RTL_XFLIP, 80+32-selection_offset, 142, loc::gettext(STR_ID("[ YES, QUIT TO MENU ]", STR_YES_QUIT_TO_MENU_HOVER)), 196, 196, 255 - help.glow);
        }
        break;
    case 20:
        font::print(PR_CEN | PR_CJK_LOW, -1, 220, loc::gettext(STR_ID("[ GRAVITRON ]", STR_IGM_GRAVITRON)), 196, 196, 255 - help.glow);

        if (graphics.flipmode)
        {
            font::print_wrap(PR_CEN, -1, 88, loc::gettext(STR_ID("Do you want to return to the secret laboratory?", STR_WANNA_RETURN_TO_SECRET_LAB)), 196, 196, 255 - help.glow, 12);
            font::print(PR_RTL_XFLIP, 80-selection_offset, 142, loc::gettext(STR_ID("[ NO, KEEP PLAYING ]", STR_NO_KEEP_PLAYING_HOVER)), 196, 196, 255 - help.glow);
            font::print(PR_RTL_XFLIP, 80 + 32, 130, loc::gettext(STR_ID("yes, return", STR_YES_RETURN)),  96, 96, 96);
        }
        else
        {
            font::print_wrap(PR_CEN, -1, 76, loc::gettext(STR_ID("Do you want to return to the secret laboratory?", STR_WANNA_RETURN_TO_SECRET_LAB)), 196, 196, 255 - help.glow, 12);
            font::print(PR_RTL_XFLIP, 80-selection_offset, 130, loc::gettext(STR_ID("[ NO, KEEP PLAYING ]", STR_NO_KEEP_PLAYING_HOVER)), 196, 196, 255 - help.glow);
            font::print(PR_RTL_XFLIP, 80 + 32, 142, loc::gettext(STR_ID("yes, return", STR_YES_RETURN)),  96, 96, 96);
        }

        break;
    case 21:
        font::print(PR_CEN | PR_CJK_LOW, -1, 220, loc::gettext(STR_ID("[ GRAVITRON ]", STR_IGM_GRAVITRON)), 196, 196, 255 - help.glow);

        if (graphics.flipmode)
        {
            font::print_wrap(PR_CEN, -1, 88, loc::gettext(STR_ID("Do you want to return to the secret laboratory?", STR_WANNA_RETURN_TO_SECRET_LAB)), 196, 196, 255 - help.glow, 12);
            font::print(PR_RTL_XFLIP, 80, 142, loc::gettext(STR_ID("no, keep playing", STR_NO_KEEP_PLAYING)), 96, 96, 96);
            font::print(PR_RTL_XFLIP, 80 + 32-selection_offset, 130, loc::gettext(STR_ID("[ YES, RETURN ]", STR_YES_RETURN_HOVER)),  196, 196, 255 - help.glow);
        }
        else
        {
            font::print_wrap(PR_CEN, -1, 76, loc::gettext(STR_ID("Do you want to return to the secret laboratory?", STR_WANNA_RETURN_TO_SECRET_LAB)), 196, 196, 255 - help.glow, 12);
            font::print(PR_RTL_XFLIP, 80, 130, loc::gettext(STR_ID("no, keep playing", STR_NO_KEEP_PLAYING)), 96, 96, 96);
            font::print(PR_RTL_XFLIP, 80 + 32-selection_offset, 142, loc::gettext(STR_ID("[ YES, RETURN ]", STR_YES_RETURN_HOVER)),  196, 196, 255 - help.glow);
        }

    }

    #ifdef __NDS__
    graphics.scroll_gl(0, 0);
    #else
    graphics.set_render_target(graphics.gameTexture);
    #endif

    if (graphics.resumegamemode || graphics.menuoffset > 0 || graphics.oldmenuoffset > 0)
    {
        graphics.menuoffrender();
    }
    else
    {
        #ifndef __NDS__
        graphics.copy_texture(graphics.menuTexture, NULL, NULL);
        #endif
    }

    // We need to draw the black screen above the menu in order to disguise it
    // being jankily brought down in glitchrunner mode when exiting to the title
    // Otherwise, there's no reason to obscure the menu
    if (GlitchrunnerMode_less_than_or_equal(Glitchrunner2_2)
        || FADEMODE_IS_FADING(graphics.fademode)
        || game.fadetomenu
        || game.fadetolab)
    {
        graphics.drawfade();
    }


    graphics.renderwithscreeneffects();

    #ifdef __NDS__
    rendermap_sub(true);
    #endif
}

#undef FLIP_PR_CJK_HIGH
#undef FLIP_PR_CJK_LOW
#undef FLIP

void teleporterrender(void)
{
    #ifdef __NDS__
    if (script.running) {
        gamerender();
        return;
    }
    if (graphics.menuoffset > 0)
    {
        graphics.lerp_freeze = true;
        graphics.drawentities();
        if (map.towermode)
        {
            graphics.drawtowerspikes();
        }
        graphics.lerp_freeze = false;
    }
    graphics.scroll_gl(0, graphics.lerp(graphics.oldmenuoffset, graphics.menuoffset));
    graphics.fill_rect(0, 0, 320, 12, 0, 0, 0);
    #endif

    #ifndef __NDS__
    graphics.set_render_target(graphics.menuTexture);
    graphics.clear();
    #endif

    const int telex = map.teleporters[game.teleport_to_teleporter].x;
    const int teley = map.teleporters[game.teleport_to_teleporter].y;

    draw_roomname_menu();

    //Background color
    graphics.fill_rect(0, 12, 320, 240, 10, 24, 26);

    #ifndef __NDS__
    rendermap();
    rendermapfog();
    rendermapcursor(false);

    // Draw a box around the currently selected teleporter

    const MapRenderData data = getmaprenderdata();

    if (game.useteleporter)
    {
        //Draw the chosen destination coordinate!
        //TODO
        //draw the coordinates //destination
        graphics.draw_rect(40 + data.xoff + (telex * 12 * data.zoom) + 1, 21 + data.yoff + (teley * 9 * data.zoom) + 1, 12 * data.zoom - 2, 9 * data.zoom - 2, 245 - (help.glow * 2), 16, 16);
        graphics.draw_rect(40 + data.xoff + (telex * 12 * data.zoom) + 3, 21 + data.yoff + (teley * 9 * data.zoom) + 3, 12 * data.zoom - 6, 9 * data.zoom - 6, 245 - (help.glow * 2), 16, 16);
    }

    // Draw the legend itself

    rendermaplegend();

    // Highlight the currently selected teleporter

    if (game.useteleporter && (help.slowsine % 16 > 8 || game.noflashingmode))
    {
        font::print(PR_FONT_8X8 | PR_FULLBOR, data.legendxoff + data.xoff + (telex * 12 * data.zoom), data.legendyoff + data.yoff + (teley * 9 * data.zoom), "💿", 255, 0, 0);
    }
    #endif

    graphics.cutscenebars();


    if (game.useteleporter)
    {
        char buffer[SCREEN_WIDTH_CHARS + 1];
        const char* final_string = interact_prompt(
            buffer,
            sizeof(buffer),
            loc::gettext(STR_ID("Press {button} to Teleport", STR_PROMPT_TELEPORT))
        );

        //Instructions!
        #ifdef __NDS__
        font::print(PR_CEN, -1, 110, loc::gettext(STR_ID("Press Left/Right to choose a Teleporter", STR_PROMPT_CHOOSE_TELE)), 220 - (help.glow), 220 - (help.glow), 255 - (help.glow / 2));
        font::print(PR_CEN, -1, 125, final_string, 220 - (help.glow), 220 - (help.glow), 255 - (help.glow / 2));
        font::print(PR_CEN | PR_3X, -1, 210 + (help.slowsine / 8 % 2) * 3, graphics.flipmode ? "⏶ ⏶ ⏶": "⏷ ⏷ ⏷", 220 - (help.glow), 220 - (help.glow), 255 - (help.glow / 2));
        #else
        font::print(PR_CEN, -1, 210, loc::gettext("Press Left/Right to choose a Teleporter"), 220 - (help.glow), 220 - (help.glow), 255 - (help.glow / 2));
        font::print(PR_CEN, -1, 225, final_string, 220 - (help.glow), 220 - (help.glow), 255 - (help.glow / 2));
        #endif
    }

    graphics.drawgui();

    if (game.advancetext)
    {
        char buffer_adv[SCREEN_WIDTH_CHARS + 1];
        vformat_buf(
            buffer_adv, sizeof(buffer_adv),
            loc::gettext(STR_ID("- Press {button} to advance text -", STR_PROMPT_ADVANCE_TEXT)),
            "button:but",
            vformat_button(ActionSet_InGame, Action_InGame_ACTION)
        );

        font::print(PR_CEN | PR_BOR, -1, graphics.flipmode ? 228 : 5, buffer_adv, 220 - (help.glow), 220 - (help.glow), 255 - (help.glow / 2));
    }

    #ifdef __NDS__
    graphics.scroll_gl(0, 0);
    #else
    graphics.set_render_target(graphics.gameTexture);
    #endif

    if (graphics.resumegamemode || graphics.menuoffset > 0 || graphics.oldmenuoffset > 0)
    {
        graphics.menuoffrender();
    }
    else
    {
        #ifndef __NDS__
        graphics.copy_texture(graphics.menuTexture, NULL, NULL);
        #endif
    }

    graphics.render();

    #ifdef __NDS__
    rendermap_sub(false);
    if (game.useteleporter) {
        graphics.draw_telecursor_sub(telex, teley, 245 - (help.glow * 2), 16, 16);
        if (help.slowsine % 16 > 8 || game.noflashingmode) {
            graphics.draw_legend_icon_sub(9, telex, teley, 2);
        }
    }
    #endif
}
