
#ifndef LOCALIZATION_IDS_H
#define LOCALIZATION_IDS_H

#ifdef __NDS__
/* This cast is an EGREGIOUS hack for the sake of saving memory.
 * Instead of storing string IDs as strings that would eat up static
 * memory, the ID value is stored in the pointer value. At the load
 * time of a script, the `fillines` macro is modified to check for
 * these cursed pointers and push back a real string with the ID
 * into the commands vector.
 */
#define IDC(string, id) (char *)(id + 1)
#define NUL(string) (char *)(0)
#else
#define IDC(string, id) string
#define NUL(string) string
#endif

enum String_ID {
    STR_LOADING,
    STR_GAME_PAUSED,
    STR_CLICK_RESUME,
    STR_M_MUTE,
    STR_N_MUTE_MUSIC,
    STR_MAKE_AND_PLAY,
    STR_M6_INSTALLED,
    STR_PLAY,
    STR_LEVELS,
    STR_OPTIONS,
    STR_TRANSLATOR,
    STR_CREDITS,
    STR_QUIT,
    STR_GAMEPLAY_OPT,
    STR_GAMEPLAY_TITLE,
    STR_GAMEPLAY_DESC,
    STR_GRAPHICS_OPT,
    STR_GRAPHICS_TITLE,
    STR_GRAPHICS_DESC,
    STR_AUDIO_OPT,
    STR_AUDIO_TITLE,
    STR_AUDIO_DESC_M6,
    STR_AUDIO_DESC,
    STR_CONTINUE,
    STR_CONTINUE_TELE,
    STR_TELE_SAVE_TITLE,
    STR_CONTINUE_QUICK,
    STR_QUICK_SAVE_TITLE,
    STR_PROCEED,
    STR_NEW_GAME,
    STR_START_NEW_GAME,
    STR_SECRET_LAB,
    STR_PLAY_MODES,
    STR_ERR_NO_LEVELS,
    STR_ERR_NO_START_POINT,
    STR_ERROR,
    STR_WARNING,
    STR_UNLOCK_MODES_OPT,
    STR_UNLOCK_MODES_TITLE,
    STR_UNLOCK_MODES_DESC,
    STR_UNLOCK_MODES_DESC_MENU,
    STR_UNLOCK_JUKEBOX,
    STR_UNLOCK_SECRET_LAB,
    STR_GAME_PAD_OPT,
    STR_GAME_PAD_OPTS_TITLE,
    STR_GAME_PAD_TITLE,
    STR_GAME_PAD_OPTS_DESC,
    STR_GAME_PAD_DESC,
    STR_LANGUAGE_OPT,
    STR_LANGUAGE_TITLE,
    STR_LANGUAGE_DESC,
    STR_UNUSED_CHANGE_LANG_TEXTBOX,
    STR_CLEAR_MAIN_DATA,
    STR_CLEAR_CUSTOM_DATA,
    STR_CLEAR_DATA_TITLE,
    STR_CLEAR_MAIN_DATA_DESC,
    STR_CLEAR_CUSTOM_DATA_DESC,
    STR_WARNING_NEW_GAME,
    STR_WANNA_DELETE_DATA,
    STR_WANNA_DELETE_QUICKSAVE,
    STR_DONT_DELETE,
    STR_YES_DELETE_ALL,
    STR_YES_DELETE_SAVE,
    STR_SOUNDTRACK_OPT,
    STR_SOUNDTRACK_TITLE,
    STR_SOUNDTRACK_DESC,
    STR_SOUNDTRACK_P6,
    STR_SOUNDTRACK_M6,
    STR_FULLSCREEN_OPT,
    STR_FULLSCREEN_TITLE,
    STR_FULLSCREEN_DESC,
    STR_MODE_WINDOWED,
    STR_MODE_FULLSCREEN,
    STR_SCALING_MODE_OPT,
    STR_SCALING_MODE_TITLE,
    STR_SCALING_MODE_DESC,
    STR_MODE_INTEGER,
    STR_MODE_STRETCH,
    STR_MODE_LETTERBOX,
    STR_RESIZE_OPT,
    STR_RESIZE_TITLE,
    STR_RESIZE_DESC,
    STR_YOU_MUST_BE_WINDOWED,
    STR_FILTER_OPT,
    STR_FILTER_TITLE,
    STR_FILTER_DESC,
    STR_MODE_LINEAR,
    STR_MODE_NEAREST,
    STR_ANALOGUE_OPT,
    STR_ANALOGUE_TITLE,
    STR_ANALOGUE_DESC,
    STR_TOGGLE_FPS_OPT,
    STR_TOGGLE_FPS_TITLE,
    STR_TOGGLE_FPS_DESC,
    STR_AT_30_FPS,
    STR_OVER_30_FPS,
    STR_VSYNC_OPT,
    STR_VSYNC_TITLE,
    STR_VSYNC_DESC,
    STR_VSYNC_OFF,
    STR_VSYNC_ON,
    STR_MUSIC_VOLUME_OPT,
    STR_MUSIC_VOLUME_TITLE,
    STR_MUSIC_VOLUME_DESC,
    STR_SOUND_VOLUME_OPT,
    STR_SOUND_VOLUME_TITLE,
    STR_SOUND_VOLUME_DESC,
    STR_CREDITS_TITLE,
    STR_V6_IS_BY,
    STR_FEATURES_MUSIC_BY,
    STR_ROOMNAMES_BY,
    STR_CPP_VERSION_BY,
    STR_BETA_TESTED_BY,
    STR_END_PICTURE_BY,
    STR_CREATED_BY,
    STR_WITH_MUSIC_BY,
    STR_ROOMS_NAMED_BY,
    STR_CPP_PORT_BY,
    STR_PATRONS,
    STR_V6_SUPPORTED_BY_PATRONS,
    STR_AND_ALSO_BY,
    STR_AND,
    STR_GH_CONTRIBUTORS,
    STR_WITH_CONTRIB_FROM,
    STR_ALSO_THANKS_TO,
    STR_YOU,
    STR_THANKS_TO_YOUR_SUPPORT,
    STR_THANK_YOU,
    STR_GOOD_LUCK,
    STR_CANT_SAVE_MODE,
    STR_WANNA_DISABLE_CUTSCENES,
    STR_DISABLE_CUTSCENES,
    STR_ENABLE_CUTSCENES,
    STR_STICK_SENS,
    STR_LOW,
    STR_MEDIUM,
    STR_HIGH,
    STR_BIND_FLIP,
    STR_BIND_ENTER,
    STR_BIND_MENU,
    STR_BIND_RESTART,
    STR_BIND_INTERACT,
    STR_BOUND_FLIP,
    STR_BOUND_ENTER,
    STR_BOUND_MENU,
    STR_BOUND_RESTART,
    STR_BOUND_INTERACT,
    STR_ERR_NO_LANG_FILES,
    STR_LANG_FOLDER,
    STR_REPO_LANG_FOLDER,
    STR_TRANSLATOR_OPTS_OPT,
    STR_TRANSLATOR_OPTS_TITLE,
    STR_TRANSLATOR_OPTS_DESC,
    STR_MAINTENANCE_OPT,
    STR_MAINTENANCE_TITLE,
    STR_OPEN_LANG_FOLDER,
    STR_MAINTENANCE_DESC,
    STR_TRANSLATE_ROOMS_OPT,
    STR_TRANSLATE_ROOMS_TITLE,
    STR_TRANSLATE_ROOMS_DESC,
    STR_NOT_ENABLED_TRANSLATOR,
    STR_MENU_TEST_OPT,
    STR_MENU_TEST_TITLE,
    STR_MENU_TEST_DESC,
    STR_CUTSCENE_TEST_OPT,
    STR_CUTSCENE_TEST_TITLE,
    STR_CUTSCENE_TEST_DESC,
    STR_FROM_CLIPBOARD,
    STR_EXPLORE_GAME_OPT,
    STR_EXPLORE_GAME_TITLE,
    STR_EXPLORE_GAME_DESC,
    STR_LIMITS_CHECK_OPT,
    STR_GLOBAL_LIMITS_CHECK_OPT,
    STR_LIMITS_CHECK_TITLE,
    STR_LIMITS_CHECK_DESC,
    STR_NO_OVERFLOWS_FOUND,
    STR_NO_OVERFLOWS_LEFT,
    STR_NOTE_DETECTION,
    STR_SYNC_LANGS_OPT,
    STR_SYNC_LANGS_TITLE,
    STR_SYNC,
    STR_SYNC_LANGS_DESC,
    STR_LANG_STATS_OPT,
    STR_GLOBAL_STATS_OPT,
    STR_STATS_TITLE,
    STR_LANG_STATS_DESC,
    STR_GLOBAL_STATS_DESC,
    STR_IF_NEW_STRINGS,
    STR_FULL_SYNCING,
    STR_SYNC_NOT_SUPPORTED,
    STR_ADVANCED_OPTS_OPT,
    STR_ADVANCED_OPTS_TITLE,
    STR_ADVANCED_OPTS_DESC,
    STR_UNFOCUS_PAUSE_OPT,
    STR_UNFOCUS_PAUSE_TITLE,
    STR_UNFOCUS_PAUSE_DESC,
    STR_UNFOCUS_PAUSE_OFF,
    STR_UNFOCUS_PAUSE_ON,
    STR_UNFOCUS_AUDIO_PAUSE_OPT,
    STR_UNFOCUS_AUDIO_PAUSE_TITLE,
    STR_UNFOCUS_AUDIO_PAUSE_DESC,
    STR_UNFOCUS_AUDIO_PAUSE_OFF,
    STR_UNFOCUS_AUDIO_PAUSE_ON,
    STR_TIMER_OPT,
    STR_TIMER_TITLE,
    STR_TIMER_DESC,
    STR_TIMER_ON,
    STR_TIMER_OFF,
    STR_SPRITES_OPT,
    STR_SPRITES_TITLE,
    STR_SPRITES_DESC,
    STR_SPRITES_TRANSLATED,
    STR_SPRITES_ALWAYS_EN,
    STR_INTERACT_BUTTON_OPT,
    STR_INTERACT_BUTTON_TITLE,
    STR_INTERACT_BUTTON_DESC,
    STR_E,
    STR_ENTER,
    STR_ESC,
    STR_ACTION,
    STR_INTERACT_BUTTON_SET,
    STR_FAKE_LOAD_OPT,
    STR_FAKE_LOAD_TITLE,
    STR_FAKE_LOAD_DESC,
    STR_FAKE_LOAD_OFF,
    STR_FAKE_LOAD_ON,
    STR_RNBG_OPT,
    STR_RNBG_TITLE,
    STR_RNBG_DESC,
    STR_RNBG_TRANSLUCENT,
    STR_RNBG_OPAQUE,
    STR_SPEEDRUN_OPTS_OPT,
    STR_SPEEDRUN_OPTS_TITLE,
    STR_SPEEDRUN_OPTS_DESC,
    STR_GLITCH_OPT,
    STR_GLITCH_TITLE,
    STR_GLITCH_DESC,
    STR_GLITCH_IS_OFF,
    STR_GLITCH_IS_VERSION,
    STR_SELECT_GLITCH,
    STR_GLITCH_NONE,
    STR_GLITCH_2_0,
    STR_GLITCH_2_2,
    STR_DELAY_OPT,
    STR_DELAY_TITLE,
    STR_DELAY_DESC,
    STR_DELAY_ON,
    STR_DELAY_OFF,
    STR_ACCESSIBILITY_OPT,
    STR_ACCESSIBILITY_TITLE,
    STR_ACCESSIBILITY_DESC,
    STR_BACKGROUND_OPT,
    STR_BACKGROUND_TITLE,
    STR_BACKGROUND_DESC,
    STR_BACKGROUND_ON,
    STR_BACKGROUND_OFF,
    STR_SCREENFX_OPT,
    STR_SCREENFX_TITLE,
    STR_SCREENFX_DESC,
    STR_SCREENFX_ON,
    STR_SCREENFX_OFF,
    STR_TEXT_OUTLINE,
    STR_TEXT_OUTLINE_TITLE,
    STR_TEXT_OUTLINE_DESC,
    STR_TEXT_OUTLINE_ON,
    STR_TEXT_OUTLINE_OFF,
    STR_INVINCIBILITY,
    STR_INVINCIBILITY_TITLE,
    STR_INVINCIBILITY_DESC,
    STR_INVINCIBILITY_ON,
    STR_INVINCIBILITY_OFF,
    STR_WANNA_ENABLE_INVINCIBILITY,
    STR_NO_RETURN_TO_OPTIONS,
    STR_YES_ENABLE,
    STR_SLOWDOWN_OPT,
    STR_SLOWDOWN_TITLE,
    STR_GAME_SPEED_TITLE,
    STR_SLOWDOWN_DESC,
    STR_GAME_SPEED_DESC,
    STR_SPEED_IS_NORMAL,
    STR_SPEED_IS_80,
    STR_SPEED_IS_60,
    STR_SPEED_IS_40,
    STR_NORMAL_SPEED,
    STR_80_SPEED,
    STR_60_SPEED,
    STR_40_SPEED,
    STR_PLAY_IM1,
    STR_PLAY_IM2,
    STR_WITH_WHO,
    STR_TIME_TRIALS_OPT,
    STR_TIME_TRIALS_TITLE,
    STR_TIME_TRIALS_DESC,
    STR_TIME_TRIALS_ARE_LEGIT,
    STR_UNLOCK_TRIALS_OPT,
    STR_UNLOCK_TRIALS_TITLE,
    STR_UNLOCK_TRIALS_SEPARATELY,
    STR_INTERMISSIONS_OPT,
    STR_INTERMISSIONS_TITLE,
    STR_INTERMISSIONS_DESC,
    STR_UNLOCK_IMS,
    STR_TO_UNLOCK_IMS,
    STR_NO_DEATH_OPT,
    STR_NO_DEATH_TITLE,
    STR_NO_DEATH_DESC,
    STR_NO_DEATH_IS_LEGIT,
    STR_UNLOCK_NO_DEATH,
    STR_TO_UNLOCK_NO_DEATH,
    STR_FLIP_MODE_OPT,
    STR_FLIP_MODE_TITLE,
    STR_FLIP_MODE_DESC,
    STR_FLIP_MODE_DESC_COMPAT,
    STR_UNLOCK_FLIP_MODE,
    STR_CURRENTLY_ENABLED,
    STR_CURRENTLY_DISABLED,
    STR_TO_UNLOCK_FLIP_MODE,
    STR_INVINCIBILITY_ENABLED,
    STR_GLITCH_ENABLED_VERSION,
    STR_FLIP_MODE_ENABLED,
    STR_WANNA_QUIT,
    STR_GAME_OVER,
    STR_REACHED,
    STR_KEEP_TRYING,
    STR_NICE_ONE,
    STR_WOW_CONGRATS,
    STR_INCREDIBLE,
    STR_UNBELIEVABLE,
    STR_ER_HOW,
    STR_WOW_MEGA,
    STR_RESCUED_ALL_CREWMATE,
    STR_NEW_TROPHY_AWARDED,
    STR_MM_TRINKETS_FOUND,
    STR_MM_NUM_DEATHS,
    STR_MM_TIME_TAKEN,
    STR_TRINKETS_FOUND,
    STR_GAME_TIME,
    STR_TOTAL_FLIPS,
    STR_TOTAL_DEATHS,
    STR_RESULTS,
    STR_TIME_TAKEN,
    STR_NUM_DEATHS,
    STR_SHINY_TRINKETS,
    STR_TIMES_DELIM,
    STR_TOTAL_TRINKETS,
    STR_TOTAL_TRINKETS_OF,
    STR_TOTAL_TRINKETS_WORDY,
    STR_SAVEBOX_TRINKETS_WORDY,
    STR_GAMECOMPLETE_TRINKET_COUNT,
    STR_RANK_UP,
    STR_RANK,
    STR_B,
    STR_A,
    STR_S,
    STR_V,
    STR_SPACE_STATION_1_OPT,
    STR_SPACE_STATION_1_TITLE,
    STR_SPACE_STATION_2_OPT,
    STR_SPACE_STATION_2_TITLE,
    STR_THE_LABORATORY_OPT,
    STR_THE_LABORATORY_TITLE,
    STR_THE_TOWER_OPT,
    STR_THE_TOWER_TITLE,
    STR_THE_WARP_ZONE_OPT,
    STR_THE_WARP_ZONE_TITLE,
    STR_THE_FINAL_LEVEL_OPT,
    STR_THE_FINAL_LEVEL_TITLE,
    STR_INTERMISSION_1_OPT,
    STR_INTERMISSION_1_TITLE,
    STR_INTERMISSION_2_OPT,
    STR_INTERMISSION_2_TITLE,
    STR_QQQ,
    STR_NOT_ATTEMPTED,
    STR_TO_UNLOCK,
    STR_RESCUE_VIOLET,
    STR_RESCUE_VICTORIA,
    STR_RESCUE_VERMILION,
    STR_RESCUE_VITELLARY,
    STR_RESCUE_VERDIGRIS,
    STR_COMPLETE_THE_GAME,
    STR_FIND_3_TRINKETS,
    STR_FIND_6_TRINKETS,
    STR_FIND_9_TRINKETS,
    STR_FIND_12_TRINKETS,
    STR_FIND_15_TRINKETS,
    STR_FIND_18_TRINKETS,
    STR_RECORDS,
    STR_TIME,
    STR_SHINY,
    STR_LIVES,
    STR_PAR_TIME,
    STR_TRIAL_TIME,
    STR_TRIAL_DEATH,
    STR_TRIAL_SHINY,
    STR_TRIAL_PAR_TIME,
    STR_BEST_RANK,
    STR_GO_CAP,
    STR_GO,
    STR_CONGRATS_TITLE,
    STR_SAVES_UPDATED,
    STR_KEEP_EXPLORING,
    STR_UNLOCKED_NEW_TRIAL,
    STR_UNLOCKED_NEW_TRIALS,
    STR_UNLOCKED_NO_DEATH,
    STR_UNLOCKED_FLIP_MODE,
    STR_UNLOCKED_IMS,
    STR_PLAY_LEVEL,
    STR_LEVEL_EDITOR,
    STR_OPEN_LEVEL_FOLDER,
    STR_SHOW_LEVEL_FOLDER_PATH,
    STR_RETURN,
    STR_RETURN_TO_LEVELS,
    STR_DONT_SHOW,
    STR_YES_REVEAL,
    STR_RETURN_TO_PLAY_MENU,
    STR_TRY_AGAIN,
    STR_OK,
    STR_NEXT_PAGE,
    STR_PREV_PAGE,
    STR_FIRST_PAGE,
    STR_LAST_PAGE,
    STR_SILENCE,
    STR_CONTINUE_SAVE,
    STR_START_FROM_BEGIN,
    STR_DELETE_SAVE,
    STR_BACK_TO_LEVELS,
    STR_EDITOR_UNSUPPORTED_DECK,
    STR_EDITOR_UNSUPPORTED,
    STR_TO_INSTALL_LEVELS,
    STR_WANNA_SHOW_LEVELS_PATH,
    STR_LEVELS_PATH,
    STR_PROMPT_START,
    STR_ACTION_IS,
    STR_PROMPT_RETURN_TO_ED,
    STR_PROMPT_ADVANCE_TEXT,
    STR_PROMPT_CONTINUE,
    STR_PROMPT_UNFREEZE,
    STR_PROMPT_FREEZE,
    STR_CURRENT_TIME,
    STR_BEST_TIME,
    STR_NEXT_TROPHY_5_SECONDS,
    STR_NEXT_TROPHY_10_SECONDS,
    STR_NEXT_TROPHY_15_SECONDS,
    STR_NEXT_TROPHY_20_SECONDS,
    STR_NEXT_TROPHY_30_SECONDS,
    STR_NEXT_TROPHY_1_MINUTE,
    STR_GOT_ALL_TROPHIES,
    STR_NEW_RECORD,
    STR_NEW_TROPHY,
    STR_PROMPT_STOP,
    STR_SUPER_GRAVITRON,
    STR_SUPER_GRAVITRON_HIGHSCORE,
    STR_MAP,
    STR_GRAV,
    STR_SHIP,
    STR_CREW,
    STR_STATS,
    STR_SAVE,
    STR_IGM_PAUSE,
    STR_IGM_QUIT,
    STR_IGM_GRAVITRON,
    STR_NO_SIGNAL,
    STR_PROMPT_WARP_SHIP,
    STR_MISSING_MALE,
    STR_MISSING_FEMALE,
    STR_MISSING_YOU,
    STR_RESCUED_MALE,
    STR_RESCUED_FEMALE,
    STR_THATS_YOU,
    STR_CANT_SAVE_IN_REPLAY,
    STR_CANT_SAVE_IN_NO_DEATH,
    STR_HOWD_YOU_GET_HERE,
    STR_CANT_SAVE_IN_SECRET_LAB,
    STR_ERR_SAVE_GAME,
    STR_ERR_SAVE_SETTINGS,
    STR_SAVED_OK,
    STR_PROMPT_SAVE,
    STR_NOTE_AUTOSAVE,
    STR_LAST_SAVE,
    STR_WANNA_RETURN_TO_MAIN,
    STR_WANNA_QUIT_UNSAVED,
    STR_WANNA_RETURN_TO_SECRET_LAB,
    STR_NO_KEEP_PLAYING,
    STR_NO_KEEP_PLAYING_HOVER,
    STR_YES_QUIT_TO_MENU,
    STR_YES_QUIT_TO_MENU_HOVER,
    STR_YES_RETURN,
    STR_YES_RETURN_HOVER,
    STR_NO_RETURN,
    STR_YES_QUIT,
    STR_RETURN_TO_GAME,
    STR_QUIT_TO_MENU,
    STR_PROMPT_CHOOSE_TELE,
    STR_PROMPT_TELEPORT,
    STR_PROMPT_TELEPORT_2,
    STR_PROMPT_EXPLODE,
    STR_PROMPT_VIOLET,
    STR_PROMPT_VITELLARY,
    STR_PROMPT_VERMILION,
    STR_PROMPT_VERDIGRIS,
    STR_PROMPT_VICTORIA,
    STR_PROMPT_TERMINAL,
    STR_PROMPT_TERMINALS,
    STR_PROMPT_INTERACT,
    STR_PROMPT_SKIP,
    STR_PASSION_FOR_EXPLORING,
    STR_PUSHING_ONWARDS,
    STR_POSITIVE_FORCE,
    STR_PRESENTING_VVVVVV,
    STR_POTENTIAL_FOR_ANYTHING,
    STR_PREDESTINED_FATE,
    STR_PIPE_DREAM,
    STR_POPULAR_POTPOURRI,
    STR_PRESSURE_COOKER,
    STR_ECROF_EVITISOP,
    STR_MAP_SETTINGS_TITLE,
    STR_EDIT_SCRIPTS,
    STR_CHANGE_MUSIC,
    STR_EDITOR_GHOSTS,
    STR_EDITOR_GHOSTS_OFF,
    STR_EDITOR_GHOSTS_ON,
    STR_LOAD_LEVEL,
    STR_SAVE_LEVEL,
    STR_QUIT_TO_MAIN,
    STR_CHANGE_NAME,
    STR_CHANGE_AUTHOR,
    STR_CHANGE_DESCRIPTION,
    STR_CHANGE_WEBSITE,
    STR_CHANGE_FONT,
    STR_ED_LEVEL_FONT_TITLE,
    STR_ED_LEVEL_FONT_DESC,
    STR_ED_FONT,
    STR_ED_MAP_MUSIC_TITLE,
    STR_ED_CURRENT_MUSIC,
    STR_ED_MUSIC_NONE,
    STR_ED_MUSIC_1,
    STR_ED_MUSIC_2,
    STR_ED_MUSIC_3,
    STR_ED_MUSIC_4,
    STR_ED_MUSIC_NA_PAUSE,
    STR_ED_MUSIC_5,
    STR_ED_MUSIC_NA_PLENARY,
    STR_ED_MUSIC_6,
    STR_ED_MUSIC_NA_ECROF,
    STR_ED_MUSIC_7,
    STR_ED_MUSIC_8,
    STR_ED_MUSIC_9,
    STR_ED_MUSIC_10,
    STR_ED_MUSIC_11,
    STR_ED_MUSIC_NA_PF_REMIX,
    STR_ED_MUSIC_ELSE,
    STR_NEXT_SONG,
    STR_PREV_SONG,
    STR_ED_BACK,
    STR_ED_SAVE_B4_QUIT,
    STR_YES_SAVE_QUIT,
    STR_NO_QUIT_UNSAVED,
    STR_RETURN_TO_EDITOR,
    STR_UNTITLED_LEVEL,
    STR_UNKNOWN_AUTHOR,
    STR_ED_TILE,
    STR_ED_SCRIPTBOX_FIRST,
    STR_ED_SCRIPTBOX_LAST,
    STR_ED_ENEMYBOUND_FIRST,
    STR_ED_ENEMYBOUND_LAST,
    STR_ED_PLATBOUND_FIRST,
    STR_ED_PLATBOUND_LAST,
    STR_ED_FIRST_CORNER,
    STR_ED_LAST_CORNER,
    STR_ED_V6_SCRIPT_EDITOR,
    STR_ED_PROMPT_ESC_RETURN,
    STR_ED_NO_SCRIPT_IDS,
    STR_ED_CREATE_A_SCRIPT,
    STR_ED_CURRENT_SCRIPT,
    STR_ED_PROMPT_PLACE_DEST,
    STR_ED_PROMPT_CANCEL,
    STR_ED_PROMPT_CHANGE_TOOL,
    STR_ED_1,
    STR_ED_2,
    STR_ED_3,
    STR_ED_4,
    STR_ED_5,
    STR_ED_6,
    STR_ED_7,
    STR_ED_8,
    STR_ED_9,
    STR_ED_0,
    STR_ED_R,
    STR_ED_T,
    STR_ED_Y,
    STR_ED_U,
    STR_ED_I,
    STR_ED_O,
    STR_ED_P,
    STR_ED_START,
    STR_ED_HINT_MENU,
    STR_ED_F1,
    STR_ED_F2,
    STR_ED_F3,
    STR_ED_F4,
    STR_ED_F5,
    STR_ED_F9,
    STR_ED_F10,
    STR_ED_W,
    STR_ED_E,
    STR_ED_S,
    STR_ED_L,
    STR_ED_SAVE_AS,
    STR_ED_LOAD,
    STR_ED_NEW_ROOM_NAME,
    STR_ED_ROOM_COORDS,
    STR_ED_SCRIPT_NAME,
    STR_ED_ROOM_TEXT,
    STR_ED_TILES_SS1,
    STR_ED_TILES_OUTSIDE,
    STR_ED_TILES_LAB,
    STR_ED_TILES_WARP_ZONE,
    STR_ED_TILES_SHIP,
    STR_ED_USING_TILESET,
    STR_ED_CHANGED_TILES_COLOR,
    STR_ED_CHANGED_ENEMY_COLOR,
    STR_ED_PLAT_SPEED_IS,
    STR_ED_RELOADED_RES,
    STR_ED_ERR_INVALID_FMT,
    STR_ED_LOADED_MAP,
    STR_ED_SAVED_MAP,
    STR_ED_ERR_LOAD_LEVEL,
    STR_ED_ERR_SAVE_LEVEL,
    STR_ED_MAPSIZE_IS,
    STR_ED_DIRECT_MODE_DISABLED,
    STR_ED_DIRECT_MODE_ENABLED,
    STR_ED_ERR_WARPLINES_EDGES,
    STR_ED_WARP_ALL,
    STR_ED_WARP_HOR,
    STR_ED_WARP_VER,
    STR_ED_WARP_OFF,
    STR_ED_ERR_NO_CHECK,
    STR_ED_ERR_MAX_TRINKETS,
    STR_ED_ERR_MAX_CREWMATES,
    STR_ED_LEVEL_QUITS_TO_MENU,
    STR_ED_LEVEL_COMPLETED,
    STR_ED_ROLLED_CREDITS,
    STR_ED_TIME_TRIAL_COMPLETED,
    STR_FMT_HMMSS,
    STR_FMT_HMMSSCC,
    STR_FMT_MSS,
    STR_FMT_MSSCC,
    STR_FMT_SCC,
    STR_POINT_99,
    STR_AREA_TIME,
    STR_LEVEL_COMPLETE,
    STR_GAME_COMPLETE,
    STR_YOU_RESCUED_CREW,
    STR_ALL_CREW_RESCUED,
    STR_ALL_CREWMATE_RESCUED,
    STR_GAME_SAVED,
    STR_ARROW_WASD_MOVE,
    STR_L_R_MOVE,
    STR_PROMPT_FLIP,
    STR_PROMPT_MAPMENU,
    STR_U_D_FLIP,
    STR_COMMS_RELAY_0,
    STR_COMMS_RELAY_1,
    STR_COMMS_RELAY_2,
    STR_COMMS_RELAY_3,
    STR_COMMS_RELAY_4,
    STR_COMMS_RELAY_5,
    STR_COMMS_RELAY_6,
    STR_CONGRATS_TRINKET,
    STR_CONGRATS_CREWMATE,
    STR_CONGRATS_SECRET_LAB,
    STR_SECRET_LAB_IS_SEPERATE,
    STR_VIRIDIAN,
    STR_VIOLET,
    STR_VITELLARY,
    STR_VERMILION,
    STR_VERDIGRIS,
    STR_VICTORA,
    STR_WITH_VITELLARY,
    STR_WITH_VERMILION,
    STR_WITH_VERDIGRIS,
    STR_WITH_VICTORIA,
    STR_STARRING,
    STR_CPT_VIRIDIAN,
    STR_DR_VIOLET,
    STR_PROF_VITELLARY,
    STR_OFC_VERMILION,
    STR_CHF_VERDIGRIS,
    STR_DR_VICTORIA,
    STR_IM1_FLOOR_VITELLARY,
    STR_IM1_FLOOR_VERMILION,
    STR_IM1_FLOOR_VERDIGRIS,
    STR_IM1_FLOOR_VICTORIA,
    STR_IM1_FLOOR_COMPANION,
    STR_IM1_CEIL_VITELLARY,
    STR_IM1_CEIL_VERMILION,
    STR_IM1_CEIL_VERDIGRIS,
    STR_IM1_CEIL_VICTORIA,
    STR_IM1_CEIL_COMPANION,
    STR_IM1_NOT_FLOOR_VITELLARY,
    STR_IM1_NOT_FLOOR_VERMILION,
    STR_IM1_NOT_FLOOR_VERDIGRIS,
    STR_IM1_NOT_FLOOR_VICTORIA,
    STR_IM1_NOT_FLOOR_COMPANION,
    STR_IM1_NOT_CEIL_VITELLARY,
    STR_IM1_NOT_CEIL_VERMILION,
    STR_IM1_NOT_CEIL_VERDIGRIS,
    STR_IM1_NOT_CEIL_VICTORIA,
    STR_IM1_NOT_CEIL_COMPANION,
    STR_IM1_WAIT_MALE,
    STR_IM1_WAIT_FEMALE,
    STR_IM1_WAIT_NONBINARY,
    STR_SURVIVE_FOR,
    STR_60_SECONDS,
    STR_THANKS_FOR,
    STR_PLAYING,
    STR_MASTERED_SS1,
    STR_MASTERED_LAB,
    STR_MASTERED_TOWER,
    STR_MASTERED_SS2,
    STR_MASTERED_WARP_ZONE,
    STR_MASTERED_FINAL,
    STR_OBTAIN_A_V_RANK,
    STR_GAME_COMPLETE_TROPHY,
    STR_COMPLETE_THE_GAME_TROPHY,
    STR_FLIP_MODE_COMPLETE,
    STR_COMPLETE_FLIP_MODE,
    STR_UNDER_50_DEATHS,
    STR_UNDER_100_DEATHS,
    STR_UNDER_250_DEATHS,
    STR_UNDER_500_DEATHS,
    STR_LAST_5_SECONDS,
    STR_LAST_10_SECONDS,
    STR_LAST_15_SECONDS,
    STR_LAST_20_SECONDS,
    STR_LAST_30_SECONDS,
    STR_LAST_1_MINUTE,
    STR_MASTER_OF_THE_UNIVERSE,
    STR_COMPLETE_NO_DEATH,
    STR_MISSING_ERROR,
    STR_FAILED_MOUNT,
    STR_LEVEL_NOT_FOUND,
    STR_ERR_PARSE_PATH,
    STR_BAD_DIMENSIONS,
    STR_ERR_WRITE_LANG,
    STR_LOCALISATION,
    STR_LOCALIZED_LED_BY,
    STR_UNUSED_TRANSLATIONS_BY,
    STR_TRANSLATORS,
    STR_PE_FONT_BY,
    STR_UNUSED_FONTS_BY,
    STR_UNUSED_OTHER_FONTS_BY,
    STR_EDITING_LQA,
    STR_ARABIC,
    STR_CATALAN,
    STR_WELSH,
    STR_GERMAN,
    STR_ESPERANTO,
    STR_SPANISH,
    STR_FRENCH,
    STR_IRISH,
    STR_ITALIAN,
    STR_JAPANESE,
    STR_KOREAN,
    STR_DUTCH,
    STR_POLISH,
    STR_BRAZIL_PORTUGUESE,
    STR_EUROPE_PORTUGUESE,
    STR_RUSSIAN,
    STR_SILESIAN,
    STR_TURKISH,
    STR_UKRAINIAN,
    STR_CHINESE_SIMPLE,
    STR_CHINESE_TRAD,
    STR_SPANISH_ES,
    STR_SPANISH_LATAM,
    STR_SPANISH_ARG,
	STR_BLANK_0,
	STR_BLANK_1,

	STR_ID_COUNT
};

enum Cutscene_String_ID {
    // "intro"
    STRC_INTRO_UH_OH, // "cyan" "Uh oh..."
    STRC_INTRO_IS_EVERYTHING_OK, // "purple" "Is everything ok?"
    STRC_INTRO_HIT_INTERFERENCE, // "cyan" "No! We've hit some kind of interference..."
    STRC_INTRO_SOMETHING_WRONG, // "cyan" "Something's wrong! We're going to crash!"
    STRC_INTRO_EVACUATE, // "cyan" "Evacuate!"
    STRC_INTRO_OH_NO, // "blue" "Oh no!"
    STRC_INTRO_OFF_THE_SHIP, // "red" "Everyone off the ship!"
    STRC_INTRO_SHOULDNT_HAPPEN, // "yellow" "This shouldn't be happening!"
    STRC_INTRO_PHEW_SCARY, // "cyan" "Phew! That was scary!"
    STRC_INTRO_WE_ALL_ESCAPED_RIGHT, // "cyan" "At least we all escaped, right guys?"
    STRC_INTRO_GUYS, // "cyan" "...guys?"
    // "firststeps"
    STRC_FIRSTSTEPS_WHY_TELE_ALONE, // "cyan" "I wonder why the ship teleported me here alone?"
    STRC_FIRSTSTEPS_HOPE_EVERYONE_OK, // "cyan" "I hope everyone else got out ok..."
    // "communicationstation"
    STRC_COMMSTATION_VIOLET_THAT_YOU, // "cyan" "Violet! Is that you?"
    STRC_COMMSTATION_CAPTAIN_YOURE_OK, // "purple" "Captain! You're ok!"
    STRC_COMMSTATION_SOMETHING_WRONG_TELE, // "purple" "Something has gone horribly wrong with the ship's teleporter!"
    STRC_COMMSTATION_EVERYONE_TELE_RANDOM, // "purple" "I think everyone has been teleported away randomly! They could be anywhere!"
    STRC_COMMSTATION_OH_NO, // "cyan" "Oh no!"
    STRC_COMMSTATION_SHIP_DAMAGED_INTACT, // "purple" "I'm on the ship - it's damaged badly, but it's still intact!"
    STRC_COMMSTATION_WHERE_CAPTAIN, // "purple" "Where are you, Captain?"
    STRC_COMMSTATION_ON_SPACESTATION, // "cyan" "I'm on some sort of space station... It seems pretty modern..."
    STRC_COMMSTATION_INTERFERENCE, // "purple" "There seems to be some sort of interference in this dimension..."
    STRC_COMMSTATION_BROADCASTING, // "purple" "I'm broadcasting the coordinates of the ship to you now."
    STRC_COMMSTATION_CANT_TELE_BACK, // "purple" "I can't teleport you back, but..."
    STRC_COMMSTATION_FIND_A_TELE, // "purple" "If YOU can find a teleporter anywhere nearby, you should be able to teleport back to me!"
    STRC_COMMSTATION_OK_ILL_TRY, // "cyan" "Ok! I'll try to find one!"
    STRC_COMMSTATION_GOOD_LUCK, // "purple" "Good luck, Captain!"
    STRC_COMMSTATION_FIND_CREW, // "purple" "I'll keep trying to find the rest of the crew..."
    // "trenchwarfare" explanation="player finds Trench Warfare trinket, if no trinkets found yet">
    STRC_TRENCHWAREFARE_WONDER, // "cyan" "Ohh! I wonder what that is?"
    STRC_TRENCHWAREFARE_TAKE_TO_SHIP, // "cyan" "I probably don't really need it, but it might be nice to take it back to the ship to study..."
    // "newtrenchwarfare" explanation="player finds Trench Warfare trinket, if other trinket already found">
    STRC_NEWTRENCHWARFARE_SHINY_THING, // "cyan" "Oh! It's another one of those shiny things!"
    STRC_NEWTRENCHWARFARE_TAKE_TO_SHIP, // "cyan" "I probably don't really need it, but it might be nice to take it back to the ship to study..."
    // "teleporterback"
    STRC_TELEBACK_A_TELE, // "cyan" "A teleporter!"
    STRC_TELEBACK_I_CAN_GET_BACK, // "cyan" "I can get back to the ship with this!"
    // "levelonecomplete_ending"
    STRC_LEVELCOMPLETEEND_CAPTAIN, // "purple" "Captain!"
    // "bigopenworld"
    STRC_BIGOPENWORLD_ANY_IDEA_CRASH, // "player" "So, Doctor - have you any idea what caused the crash?"
    STRC_BIGOPENWORLD_BIZARRE_SIGNAL, // "purple" "There's some sort of bizarre signal here that's interfering with our equipment..."
    STRC_BIGOPENWORLD_QUANTUM_POSITION, // "purple" "It caused the ship to lose its quantum position, collapsing us into this dimension!"
    STRC_BIGOPENWORLD_OH_NO, // "player" "Oh no!"
    STRC_BIGOPENWORLD_ABLE_FIX_SHIP, // "purple" "But I think we should be able to fix the ship and get out of here..."
    STRC_BIGOPENWORLD_FIND_CREW, // "purple" "... as long as we can find the rest of the crew."
    STRC_BIGOPENWORLD_DONT_KNOW, // "purple" "We really don't know anything about this place..."
    STRC_BIGOPENWORLD_FRIENDS_ANYWHERE, // "purple" "Our friends could be anywhere - they could be lost, or in danger!"
    STRC_BIGOPENWORLD_CAN_TELE_BACK, // "player" "Can they teleport back here?"
    STRC_BIGOPENWORLD_FIND_COMM, // "purple" "Not unless they find some way to communicate with us!"
    STRC_BIGOPENWORLD_CANT_PICKUP_SIGNAL, // "purple" "We can't pick up their signal and they can't teleport here unless they know where the ship is..."
    STRC_BIGOPENWORLD_SO_WHAT_DO, // "player" "So what do we do?"
    STRC_BIGOPENWORLD_FIND_THEM, // "purple" "We need to find them! Head out into the dimension and look for anywhere they might have ended up..."
    STRC_BIGOPENWORLD_OK_WHERE_START, // "player" "Ok! Where do we start?"
    STRC_BIGOPENWORLD_WITH_SCANNERS, // "purple" "Well, I've been trying to find them with the ship's scanners!"
    STRC_BIGOPENWORLD_FOUND_SOMETHING, // "purple" "It's not working, but I did find something..."
    STRC_BIGOPENWORLD_HIGH_ENERGY, // "purple" "These points show up on our scans as having high energy patterns!"
    STRC_BIGOPENWORLD_CHANCE_TELE, // "purple" "There's a good chance they're teleporters - which means they're probably built near something important..."
    STRC_BIGOPENWORLD_START_LOOKING, // "purple" "They could be a very good place to start looking."
    STRC_BIGOPENWORLD_ILL_HEAD_OUT, // "player" "Ok! I'll head out and see what I can find!"
    STRC_BIGOPENWORLD_HERE_IF_NEED_HELP, // "purple" "I'll be right here if you need any help!"
    // "bigopenworldskip"
    STRC_BIGOPENWORLDSKIP_HERE_IF_NEED_HELP, // "purple" "I'll be right here if you need any help!"
    // "talkpurple_intro"
    STRC_TALKPURPLE_INTRO_OVERWHELMED, // "player" "I'm feeling a bit overwhelmed, Doctor."
    STRC_TALKPURPLE_INTRO_WHERE_BEGIN, // "player" "Where do I begin?"
    STRC_TALKPURPLE_INTRO_CHECK_MAP, // "purple" "Remember that you can press {b_map} to check where you are on the map!"
    STRC_TALKPURPLE_INTRO_LOOK_AREAS, // "purple" "Look for areas where the rest of the crew might be..."
    STRC_TALKPURPLE_INTRO_LOST_TELE_SHIP, // "purple" "If you get lost, you can get back to the ship from any teleporter."
    STRC_TALKPURPLE_INTRO_DONT_WORRY, // "purple" "And don't worry! We'll find everyone!"
    STRC_TALKPURPLE_INTRO_WILL_BE_OK, // "purple" "Everything will be ok!"
    // "talkpurple_3" explanation="only one player string is shown">
    STRC_TALKPURPLE_3_YOU_OK_CAPTAIN, // "purple" "Are you doing ok, Captain?"
    STRC_TALKPURPLE_3_WORRIED_VICTORIA, // "player" "I'm worried about Victoria, Doctor!"
    STRC_TALKPURPLE_3_WORRIED_VITELLARY, // "player" "I'm worried about Vitellary, Doctor!"
    STRC_TALKPURPLE_3_WORRIED_VERDIGRIS, // "player" "I'm worried about Verdigris, Doctor!"
    STRC_TALKPURPLE_3_WORRIED_VERMILION, // "player" "I'm worried about Vermilion, Doctor!"
    STRC_TALKPURPLE_3_WORRIED_YOU, // "player" "I'm worried about you, Doctor!"
    STRC_TALKPURPLE_3_DONT_WORRY, // "purple" "Oh - well, don't worry, they'll show up!"
    STRC_TALKPURPLE_3_HAVE_LOLLIPOP, // "purple" "Here! Have a lollipop!"
    // "trinketcollector" explanation="if no trinkets found yet">
    STRC_TRINKETCOLLECTOR_STORE_THING, // "cyan" "This seems like a good place to store anything I find out there..."
    STRC_TRINKETCOLLECTOR_VICTORIA_STUDY, // "cyan" "Victoria loves to study the interesting things we find on our adventures!"
    // "newtrinketcollector" explanation="if at least one trinket found">
    STRC_NEWTRINKETCOLLECTOR_STORE_SHINY, // "cyan" "This seems like a good place to store those shiny things."
    STRC_NEWTRINKETCOLLECTOR_VICTORIA_STUDY, // "cyan" "Victoria loves to study the interesting things we find on our adventures!"
    // "new2trinketcollector"
    STRC_NEW2TRINKETCOLLECTOR_HOPE_SHES_OK, // "cyan" "I hope she's ok..."
    // "rescuegreen" explanation="nuance: `she's BACK on the ship` means more `she's home` and not `she has returned to the ship`. She has never left the ship">
    STRC_RESCUEGREEN_CAPTAIN_IVE_WORRIED, // "green" "Captain! I've been so worried!"
    STRC_RESCUEGREEN_VERDIGRIS_YOURE_OK, // "player" "Chief Verdigris! You're ok!"
    STRC_RESCUEGREEN_TRYING_GET_OUT, // "green" "I've been trying to get out, but I keep going around in circles..."
    STRC_RESCUEGREEN_COME_FROM_SHIP, // "player" "I've come from the ship. I'm here to teleport you back to it."
    STRC_RESCUEGREEN_IS_EVERYONE_ALRIGHT, // "green" "Is everyone else alright? Is Violet..."
    STRC_RESCUEGREEN_SHES_ON_SHIP, // "player" "She's fine - she's back on the ship!"
    STRC_RESCUEGREEN_GET_GOING, // "green" "Oh! Great - Let's get going, then!"
    // "rescueblue"
    STRC_RESCUEBLUE_OH_NO_CAPTAIN, // "blue" "Oh no! Captain! Are you stuck here too?"
    STRC_RESCUEBLUE_HERE_TO_RESCUE, // "player" "It's ok - I'm here to rescue you!"
    STRC_RESCUEBLUE_LET_ME_EXPLAIN, // "player" "Let me explain everything..."
    STRC_RESCUEBLUE_WHAT, // "blue" "What? I didn't understand any of that!"
    STRC_RESCUEBLUE_DONT_WORRY, // "player" "Oh... well, don't worry."
    STRC_RESCUEBLUE_FOLLOW_ME, // "player" "Follow me! Everything will be alright!"
    STRC_RESCUEBLUE_SNIFF_REALLY, // "blue" "Sniff... Really?"
    STRC_RESCUEBLUE_OK_THEN, // "blue" "Ok then!"
    // "rescuered"
    STRC_RESCUERED_CAPTAIN, // "red" "Captain!"
    STRC_RESCUERED_GLAD_TO_SEE_YOU, // "red" "Am I ever glad to see you! I thought I was the only one to escape the ship..."
    STRC_RESCUERED_VERMILION_KNEW_BE_OK, // "player" "Vermilion! I knew you'd be ok!"
    STRC_RESCUERED_WHATS_SITUATION, // "red" "So, what's the situation?"
    STRC_RESCUERED_I_SEE, // "red" "I see! Well, we'd better get back then."
    STRC_RESCUERED_THERES_TELE, // "red" "There's a teleporter in the next room."
    // "rescueyellow"
    STRC_RESCUEYELLOW_AH_VIRIDIAN, // "yellow" "Ah, Viridian! You got off the ship alright too?"
    STRC_RESCUEYELLOW_GOOD_TO_SEE_YOU, // "player" "It's good to see you're alright, Professor!"
    STRC_RESCUEYELLOW_IS_SHIP_OK, // "yellow" "Is the ship ok?"
    STRC_RESCUEYELLOW_DAMAGED_VIOLET_FIXING, // "player" "It's badly damaged, but Violet's been working on fixing it."
    STRC_RESCUEYELLOW_COULD_USE_YOUR_HELP, // "player" "We could really use your help..."
    STRC_RESCUEYELLOW_OF_COURSE, // "yellow" "Ah, of course!"
    STRC_RESCUEYELLOW_BACKGROUND_INTERFERENCE, // "yellow" "The background interference in this dimension prevented the ship from finding a teleporter when we crashed!"
    STRC_RESCUEYELLOW_TELE_DIFFERENT_LOCATIONS, // "yellow" "We've all been teleported to different locations!"
    STRC_RESCUEYELLOW_SOUNDS_RIGHT, // "player" "Er, that sounds about right!"
    STRC_RESCUEYELLOW_BACK_TO_THE_SHIP, // "yellow" "Let's get back to the ship, then!"
    STRC_RESCUEYELLOW_AFTER_YOU, // "yellow" "After you, Captain!"
    // "int1blue_1"
    STRC_INT1BLUE_1_WAAAA, // "blue" "Waaaa!" case="1"
    STRC_INT1BLUE_1_CAPTAIN_YOU_OK, // "blue" "Captain! Are you ok?"
    STRC_INT1BLUE_1_IM_OK, // "player" "I'm ok... this... this isn't the ship..."
    STRC_INT1BLUE_1_WHERE_ARE_WE, // "player" "Where are we?"
    STRC_INT1BLUE_1_WAAAA2, // "blue" "Waaaa!" case="2"
    STRC_INT1BLUE_1_GONE_WRONG, // "player" "Something's gone wrong... We should look for a way back!"
    // "int1blue_2"
    STRC_INT1BLUE_2_FOLLOW_ME, // "player" "Follow me! I'll help you!"
    STRC_INT1BLUE_2_PROMISE_WONT_LEAVE, // "blue" "Promise you won't leave without me!"
    STRC_INT1BLUE_2_I_PROMISE, // "player" "I promise! Don't worry!"
    // "int1blue_3"
    STRC_INT1BLUE_3_YOU_OK_DOCTOR, // "player" "Are you ok down there, Doctor?"
    STRC_INT1BLUE_3_WANNA_GO_HOME, // "blue" "I wanna go home!"
    STRC_INT1BLUE_3_WHERE_ARE_WE, // "blue" "Where are we? How did we even get here?"
    STRC_INT1BLUE_3_INTERFERENCE_TELE, // "player" "Well, Violet did say that the interference in the dimension we crashed in was causing problems with the teleporters..."
    STRC_INT1BLUE_3_SOMETHING_WRONG, // "player" "I guess something went wrong..."
    STRC_INT1BLUE_3_FIND_ANOTHER_TELE, // "player" "But if we can find another teleporter, I think we can get back to the ship!"
    STRC_INT1BLUE_3_SNIFF, // "blue" "Sniff..."
    // "int1blue_4" explanation="the split paths merge">
    STRC_INT1BLUE_4_CAPTAIN_WAIT, // "blue" "Captain! Captain! Wait for me!"
    STRC_INT1BLUE_4_DONT_LEAVE_ME, // "blue" "Please don't leave me behind! I don't mean to be a burden!"
    STRC_INT1BLUE_4_IM_SCARED, // "blue" "I'm scared!"
    STRC_INT1BLUE_4_DONT_WORRY, // "player" "Oh... don't worry Victoria, I'll look after you!"
    // "int1blue_5"
    STRC_INT1BLUE_5_NEVER_GETTING_OUT, // "blue" "We're never going to get out of here, are we?"
    STRC_INT1BLUE_5_DONT_KNOW, // "player" "I.. I don't know..."
    STRC_INT1BLUE_5_DONT_KNOW_WHERE_OR_HOW, // "player" "I don't know where we are or how we're going to get out..."
    // "int1blue_6"
    STRC_INT1BLUE_6_LOST_FOREVER, // "blue" "We're going to be lost forever!"
    STRC_INT1BLUE_6_NOT_THAT_BAD, // "player" "Ok, come on... Things aren't that bad."
    STRC_INT1BLUE_6_NEARLY_HOME, // "player" "I have a feeling that we're nearly home!"
    STRC_INT1BLUE_6_ANOTHER_TELE, // "player" "We can't be too far from another teleporter!"
    STRC_INT1BLUE_6_HOPE_YOURE_RIGHT, // "blue" "I hope you're right, captain..."
    // "int1blue_7"
    STRC_INT1BLUE_7_YOU_WERE_RIGHT, // "blue" "Captain! You were right! It's a teleporter!"
    STRC_INT1BLUE_7_PHEW, // "player" "Phew! You had me worried for a while there... I thought we were never going to find one."
    STRC_INT1BLUE_7_REALLY, // "blue" "What? Really?"
    STRC_INT1BLUE_7_BACK_TO_SHIP, // "player" "Anyway, let's go back to the ship."
    // "int1green_1"
    STRC_INT1GREEN_1_HUH_NOT_SHIP, // "green" "Huh? This isn't the ship..."
    STRC_INT1GREEN_1_CAPTAIN_WHATS_GOING_ON, // "green" "Captain! What's going on?"
    STRC_INT1GREEN_1_DONT_KNOW, // "player" "I... I don't know!"
    STRC_INT1GREEN_1_WHERE_ARE_WE, // "player" "Where are we?"
    STRC_INT1GREEN_1_GONE_WRONG_TELE, // "green" "Uh oh, this isn't good... Something must have gone wrong with the teleporter!"
    STRC_INT1GREEN_1_NO_NEED_PANIC, // "player" "Ok... no need to panic!"
    STRC_INT1GREEN_1_LOOK_FOR_ANOTHER, // "player" "Let's look for another teleporter!"
    // "int1green_2"
    STRC_INT1GREEN_2_THIS_WAY, // "player" "Let's go this way!"
    STRC_INT1GREEN_2_AFTER_YOU, // "green" "After you, Captain!"
    // "int1green_3" explanation="just like in rescuegreen, `Violet is back on the ship` does not mean she was ever off the ship and has *returned* to it. Or maybe Verdigris thinks Violet was warped off the ship as well just like him and she *has* made her way back to the ship?">
    STRC_INT1GREEN_3_SO_VIOLETS_OK, // "green" "So Violet's back on the ship? She's really ok?"
    STRC_INT1GREEN_3_SHES_FINE, // "player" "She's fine! She helped me find my way back!"
    STRC_INT1GREEN_3_PHEW_WAS_WORRIED, // "green" "Oh, phew! I was worried about her."
    STRC_INT1GREEN_3_I_HAVE_SECRET, // "green" "Captain, I have a secret..."
    STRC_INT1GREEN_3_LIKE_VIOLET, // "green" "I really like Violet!"
    STRC_INT1GREEN_3_THAT_SO, // "player" "Is that so?"
    STRC_INT1GREEN_3_PROMISE_WONT_TELL, // "green" "Please promise you won't tell her!"
    // "int1green_4" explanation="the split paths merge">
    STRC_INT1GREEN_4_HEY_AGAIN, // "green" "Hey again!"
    STRC_INT1GREEN_4_HEY, // "player" "Hey!"
    STRC_INT1GREEN_4_YOU_OK, // "player" "Are you doing ok?"
    STRC_INT1GREEN_4_THINK_SO, // "green" "I think so! I really hope we can find a way back to the ship..."
    // "int1green_5"
    STRC_INT1GREEN_5_ABOUT_VIOLET, // "green" "So, about Violet..."
    STRC_INT1GREEN_5_UM_YEAH, // "player" "Um, yeah?"
    STRC_INT1GREEN_5_ANY_ADVICE, // "green" "Do you have any advice?"
    STRC_INT1GREEN_5_OH_EX, // "player" "Oh!"
    STRC_INT1GREEN_5_HMM, // "player" "Hmm..."
    STRC_INT1GREEN_5_BE_YOURSELF, // "player" "Um... you should... be yourself!"
    STRC_INT1GREEN_5_OH, // "green" "Oh."
    STRC_INT1GREEN_5_THANKS_CAPTAIN, // "green" "Thanks Captain!"
    // "int1green_6"
    STRC_INT1GREEN_6_ABLE_FIX_SHIP, // "player" "So, do you think you'll be able to fix the ship?"
    STRC_INT1GREEN_6_DEPENDS_HOW_BAD, // "green" "Depends on how bad it is... I think so, though!"
    STRC_INT1GREEN_6_NOT_VERY_HARD, // "green" "It's not very hard, really. The basic dimensional warping engine design is pretty simple, and if we can get that working we shouldn't have any trouble getting home."
    STRC_INT1GREEN_6_OH_GOOD, // "player" "Oh! Good!"
    // "int1green_7"
    STRC_INT1GREEN_7_FINALLY_TELE, // "green" "Finally! A teleporter!"
    STRC_INT1GREEN_7_WAS_WORRIED, // "green" "I was getting worried we wouldn't find one..."
    STRC_INT1GREEN_7_BACK_TO_SHIP, // "player" "Let's head back to the ship!"
    // "int1red_1"
    STRC_INT1RED_1_WHERE_ARE_WE, // "red" "Wow! Where are we?"
    STRC_INT1RED_1_ISNT_RIGHT_TELE, // "player" "This... isn't right... Something must have gone wrong with the teleporter!"
    STRC_INT1RED_1_OH_WELL, // "red" "Oh well... We can work it out when we get back to the ship!"
    STRC_INT1RED_1_GO_EXPLORING, // "red" "Let's go exploring!"
    STRC_INT1RED_1_OK_THEN, // "player" "Ok then!"
    // "int1red_2"
    STRC_INT1RED_2_FOLLOW_ME, // "player" "Follow me!"
    STRC_INT1RED_2_AYE_AYE_CAPTAIN, // "red" "Aye aye, Captain!"
    // "int1red_3"
    STRC_INT1RED_3_VIRIDIAN_HOW_CRASH, // "red" "Hey Viridian... how did the crash happen, exactly?"
    STRC_INT1RED_3_DONT_KNOW, // "player" "Oh, I don't really know - some sort of interference..."
    STRC_INT1RED_3_SOMETHING_SCIENCY, // "player" "...or something sciencey like that. It's not really my area."
    STRC_INT1RED_3_ABLE_FIX_SHIP, // "red" "Ah! Well, do you think we'll be able to fix the ship and go home?"
    STRC_INT1RED_3_OF_COURSE, // "player" "Of course! Everything will be ok!"
    // "int1red_4" explanation="the split paths merge">
    STRC_INT1RED_4_HI_AGAIN, // "red" "Hi again! You doing ok?"
    STRC_INT1RED_4_THINK_SO, // "player" "I think so! But I really want to get back to the ship..."
    STRC_INT1RED_4_WELL_BE_OK, // "red" "We'll be ok! If we can find a teleporter somewhere we should be able to get back!"
    // "int1red_5"
    STRC_INT1RED_5_WE_THERE_YET, // "red" "Are we there yet?"
    STRC_INT1RED_5_GETTING_CLOSER, // "player" "We're getting closer, I think..."
    STRC_INT1RED_5_I_HOPE, // "player" "I hope..."
    // "int1red_6"
    STRC_INT1RED_6_WONDER_WHERE, // "player" "I wonder where we are, anyway?"
    STRC_INT1RED_6_SEEMS_DIFFERENT, // "player" "This seems different from that dimension we crashed in, somehow..."
    STRC_INT1RED_6_DUNNO, // "red" "I dunno... But we must be close to a teleporter by now..."
    // "int1red_7"
    STRC_INT1RED_7_WERE_THERE, // "player" "We're there!"
    STRC_INT1RED_7_TOLD_YOU, // "red" "See? I told you! Let's get back to the ship!"
    // "int1yellow_1"
    STRC_INT1YELLOW_1_INTERESTING, // "yellow" "Oooh! This is interesting..."
    STRC_INT1YELLOW_1_CAPTAIN_BEEN_HERE_BEFORE, // "yellow" "Captain! Have you been here before?"
    STRC_INT1YELLOW_1_WHAT_WHERE, // "player" "What? Where are we?"
    STRC_INT1YELLOW_1_DEFLECTED_TELE, // "yellow" "I suspect something deflected our teleporter transmission! This is somewhere new..."
    STRC_INT1YELLOW_1_OH_NO, // "player" "Oh no!"
    STRC_INT1YELLOW_1_FIND_TELE, // "player" "We should try to find a teleporter and get back to the ship..."
    // "int1yellow_2"
    STRC_INT1YELLOW_2_FOLLOW_ME, // "player" "Follow me!"
    STRC_INT1YELLOW_2_BEHIND_YOU_CAPTAIN, // "yellow" "Right behind you, Captain!"
    // "int1yellow_3"
    STRC_INT1YELLOW_3_WHAT_MAKE_OF_THIS, // "player" "What do you make of all this, Professor?"
    STRC_INT1YELLOW_3_DIMENSION_INTERFERENCE, // "yellow" "I'm guessing this dimension has something to do with the interference that caused us to crash!"
    STRC_INT1YELLOW_3_FIND_CAUSE_HERE, // "yellow" "Maybe we'll find the cause of it here?"
    STRC_INT1YELLOW_3_WOW_REALLY, // "player" "Oh wow! Really?"
    STRC_INT1YELLOW_3_JUST_A_GUESS, // "yellow" "Well, it's just a guess. I'll need to get back to the ship before I can do any real tests..."
    // "int1yellow_4" explanation="the split paths merge, and Vitellary sees a checkpoint">
    STRC_INT1YELLOW_4_WHAT_THAT, // "yellow" "Ohh! What was that?"
    STRC_INT1YELLOW_4_WHAT_WHAT, // "player" "What was what?"
    STRC_INT1YELLOW_4_BIG_C_THING, // "yellow" "That big... C thing! I wonder what it does?"
    STRC_INT1YELLOW_4_DONT_KNOW, // "player" "Em... I don't really know how to answer that question..."
    STRC_INT1YELLOW_4_NOT_ACKNOWLEDGE, // "player" "It's probably best not to acknowledge that it's there at all."
    STRC_INT1YELLOW_4_BACK_TO_SHIP_STUDY, // "yellow" "Maybe we should take it back to the ship to study it?"
    STRC_INT1YELLOW_4_WE_SHOULDNT, // "player" "We really shouldn't think about it too much... Let's keep moving!"
    // "int1yellow_5"
    STRC_INT1YELLOW_5_ODD_DIMENSION, // "yellow" "You know, there's something really odd about this dimension..."
    STRC_INT1YELLOW_5_YEAH, // "player" "Yeah?"
    STRC_INT1YELLOW_5_BETWEEN_DIMENSIONS, // "yellow" "We shouldn't really be able to move between dimensions with a regular teleporter..."
    STRC_INT1YELLOW_5_ISNT_PROPER_DIMENSION, // "yellow" "Maybe this isn't a proper dimension at all?"
    STRC_INT1YELLOW_5_POLAR_DIMENSION, // "yellow" "Maybe it's some kind of polar dimension? Something artificially created for some reason?"
    STRC_INT1YELLOW_5_CANT_WAIT_SHIP, // "yellow" "I can't wait to get back to the ship. I have a lot of tests to run!"
    // "int1yellow_6"
    STRC_INT1YELLOW_6_WORTH_EXPLORING, // "yellow" "I wonder if there's anything else in this dimension worth exploring?"
    STRC_INT1YELLOW_6_MAYBE, // "player" "Maybe... but we should probably just focus on finding the rest of the crew for now..."
    // "int1yellow_7"
    STRC_INT1YELLOW_7_AT_LAST, // "yellow" "At last!"
    STRC_INT1YELLOW_7_BACK_TO_SHIP, // "yellow" "Let's go back to the ship!"
    // "intermission_2"
    STRC_INTERMISSION_2_UH_OH, // "player" "Uh oh..."
    STRC_INTERMISSION_2_NOT_AGAIN, // "player" "Not again!"
    // "int2intro_blue"
    STRC_INT2INTRO_BLUE_WHERE_ARE_YOU, // "player" "Victoria? Where are you?"
    STRC_INT2INTRO_BLUE_HELP, // "blue" "Help!"
    STRC_INT2INTRO_BLUE_HANG_ON, // "player" "Hang on! I'll save you!"
    // "int2intro_green"
    STRC_INT2INTRO_GREEN_WHERE_ARE_YOU, // "player" "Verdigris? Where are you?"
    STRC_INT2INTRO_GREEN_AAGGHH, // "green" "Aaagghh!"
    STRC_INT2INTRO_GREEN_HANG_ON, // "player" "Hang on! I'll save you!"
    // "int2intro_red"
    STRC_INT2INTRO_RED_WHERE_ARE_YOU, // "player" "Vermilion? Where are you?"
    STRC_INT2INTRO_RED_WHEEEEE, // "red" "Wheeeee!"
    STRC_INT2INTRO_RED_HANG_ON, // "player" "Hang on! I'll save you!"
    // "int2intro_yellow"
    STRC_INT2INTRO_YELLOW_WHERE_ARE_YOU, // "player" "Vitellary? Where are you?"
    STRC_INT2INTRO_YELLOW_CAPTAIN, // "yellow" "Captain!"
    STRC_INT2INTRO_YELLOW_HANG_ON, // "player" "Hang on! I'll save you!"
    // "int2_blue" explanation="after gravitron">
    STRC_INT2_BLUE_GONNA_BE_SICK, // "blue" "I think I'm going to be sick..."
    STRC_INT2_BLUE_FEEL_DIZZY, // "player" "I feel dizzy..."
    // "int2_green" explanation="after gravitron">
    STRC_INT2_GREEN_PHEW_YOURE_OK, // "green" "Phew! You're ok!"
    STRC_INT2_GREEN_FEEL_DIZZY, // "player" "I feel dizzy..."
    // "int2_red" explanation="after gravitron">
    STRC_INT2_RED_AGAIN_AGAIN, // "red" "Again! Let's go again!"
    STRC_INT2_RED_FEEL_DIZZY, // "player" "I feel dizzy..."
    // "int2_yellow" explanation="after gravitron">
    STRC_INT2_YELLOW_INTERESTING, // "yellow" "That was interesting, wasn't it?"
    STRC_INT2_YELLOW_FEEL_DIZZY, // "player" "I feel dizzy..."
    // "talkpurple_1"
    STRC_TALKPURPLE_1_HOPE_VERDIGRIS_ALRIGHT, // "purple" "... I hope Verdigris is alright."
    STRC_TALKPURPLE_1_HED_HELP_FIX, // "purple" "If you can find him, he'd be a big help fixing the ship!"
    // "talkpurple_2"
    STRC_TALKPURPLE_2_VERDIGRIS_BRAVE_SMART, // "purple" "Chief Verdigris is so brave and ever so smart!"
    // "talkpurple_4"
    STRC_TALKPURPLE_4_WELCOME_BACK, // "purple" "Welcome back, Captain!"
    STRC_TALKPURPLE_4_VICTORIA_HAPPY, // "purple" "I think Victoria is quite happy to be back on the ship."
    STRC_TALKPURPLE_4_SHE_GETS_HOMESICK, // "purple" "She really doesn't like adventuring. She gets very homesick!"
    // "talkpurple_5" explanation="only one of the last 6 strings is shown">
    STRC_TALKPURPLE_5_VERMILION_CALLED, // "purple" "Vermilion called in to say hello!"
    STRC_TALKPURPLE_5_HELP_FIND_CREW, // "purple" "He's really looking forward to helping you find the rest of the crew!"
    STRC_TALKPURPLE_5_HELP_FIND_VICTORIA, // "purple" "He's really looking forward to helping you find Victoria!"
    STRC_TALKPURPLE_5_HELP_FIND_VITELLARY, // "purple" "He's really looking forward to helping you find Vitellary!"
    STRC_TALKPURPLE_5_HELP_FIND_VERDIGRIS, // "purple" "He's really looking forward to helping you find Verdigris!"
    STRC_TALKPURPLE_5_HELP_FIND_VERMILION, // "purple" "He's really looking forward to helping you find Vermilion!"
    STRC_TALKPURPLE_5_HELP_FIND_YOU, // "purple" "He's really looking forward to helping you find you!"
    // "talkpurple_6"
    STRC_TALKPURPLE_6_FOUND_VERDIGRIS, // "purple" "Captain! You found Verdigris!"
    STRC_TALKPURPLE_6_THANK_YOU_MUCH, // "purple" "Thank you so much!"
    // "talkpurple_7"
    STRC_TALKPURPLE_7_GLAD_VITELLARY_OK, // "purple" "I'm glad Professor Vitellary is ok!"
    STRC_TALKPURPLE_7_HE_HAD_QUESTIONS, // "purple" "He had lots of questions for me about this dimension."
    STRC_TALKPURPLE_7_ALREADY_RESEARCH, // "purple" "He's already gotten to work with his research!"
    // "talkpurple_intermission1"
    STRC_TALKPURPLE_INT1_STRANGE_TELE_TO_SHIP, // "player" "Doctor, something strange happened when we teleported back to the ship..."
    STRC_TALKPURPLE_INT1_GOT_LOST_DIMENSION, // "player" "We got lost in another dimension!"
    STRC_TALKPURPLE_INT1_OH_NO, // "purple" "Oh no!"
    STRC_TALKPURPLE_INT1_MAYBE_DIMENSION_INTERFERENCE, // "purple" "Maybe that dimension has something to do with the interference that caused us to crash here?"
    STRC_TALKPURPLE_INT1_ILL_LOOK_INTO_IT, // "purple" "I'll look into it..."
    // "talkpurple_intermission2"
    STRC_TALKPURPLE_INT2_IT_HAPPENED_AGAIN, // "player" "Doctor! Doctor! It happened again!"
    STRC_TALKPURPLE_INT2_WEIRD_DIMENSION, // "player" "The teleporter brought us to that weird dimension..."
    STRC_TALKPURPLE_INT2_DEFINITELY_STRANGE, // "purple" "Hmm, there's definitely something strange happening..."
    STRC_TALKPURPLE_INT2_FIND_SOURCE, // "purple" "If only we could find the source of that interference!"
    // "talkpurple_intermission3"
    STRC_TALKPURPLE_INT3_STRANGE_TELE_TO_SHIP, // "player" "Doctor, something strange has been happening when we teleport back to the ship..."
    STRC_TALKPURPLE_INT3_WEIRD_DIMENSION, // "player" "We keep getting brought to another weird dimension!"
    STRC_TALKPURPLE_INT3_OH_NO, // "purple" "Oh no!"
    STRC_TALKPURPLE_INT3_MAYBE_DIMENSION_INTERFERENCE, // "purple" "Maybe that dimension has something to do with the interference that caused us to crash here?"
    STRC_TALKPURPLE_INT3_DEFINITELY_STRANGE, // "purple" "Hmm, there's definitely something strange happening..."
    STRC_TALKPURPLE_INT3_FIND_SOURCE, // "purple" "If only we could find the source of that interference!"
    // "talkpurple_8"
    STRC_TALKPURPLE_8_TURNED_OFF_SOURCE, // "purple" "Hey Captain! Now that you've turned off the source of the interference, we can warp everyone back to the ship instantly, if we need to!"
    STRC_TALKPURPLE_8_SHIP_OPTION, // "purple" "Any time you want to come back to the ship, just select the new SHIP option in your menu!"
    // "talkgreen_1"
    STRC_TALKGREEN_1_IM_ENGINEER, // "green" "I'm an engineer!"
    // "talkgreen_2"
    STRC_TALKGREEN_2_CAN_FIX_SHIP, // "green" "I think I can get this ship moving again, but it's going to take a while..."
    // "talkgreen_3"
    STRC_TALKGREEN_3_VICTORIA_MENTIONED_LAB, // "green" "Victoria mentioned something about a lab? I wonder if she found anything down there?"
    // "talkgreen_4"
    STRC_TALKGREEN_4_VERMILIONS_BACK_YEY, // "green" "Vermilion's back! Yey!"
    // "talkgreen_5"
    STRC_TALKGREEN_5_PROF_HAD_QUESTIONS, // "green" "The Professor had lots of questions about this dimension for me..."
    STRC_TALKGREEN_5_DONT_KNOW_MUCH, // "green" "We still don't really know that much, though."
    STRC_TALKGREEN_5_WHATS_CAUSING_INTERFERENCE, // "green" "Until we work out what's causing that interference, we can't go anywhere."
    // "talkgreen_6"
    STRC_TALKGREEN_6_GLAD_VIOLETS_ALRIGHT, // "green" "I'm so glad that Violet's alright!"
    // "talkgreen_7"
    STRC_TALKGREEN_7_RELATED_DIMENSION, // "green" "That other dimension we ended up in must be related to this one, somehow..."
    // "talkgreen_8"
    STRC_TALKGREEN_8_ANTENNAS_BROKEN, // "green" "The antenna's broken! This is going to be very hard to fix..."
    // "talkgreen_9"
    STRC_TALKGREEN_9_WARPED_INTO_ROCK, // "green" "It looks like we were warped into solid rock when we crashed!"
    STRC_TALKGREEN_9_HARD_TO_SEPARATE, // "green" "Hmm. It's going to be hard to separate from this..."
    // "talkgreen_10"
    STRC_TALKGREEN_10_SHIPS_FIXED, // "green" "The ship's all fixed up. We can leave at a moment's notice!"
    // "talkred_1"
    STRC_TALKRED_1_DONT_WORRY_SIR, // "red" "Don't worry, Sir!"
    STRC_TALKRED_1_WELL_FIND_WAY_OUT, // "red" "We'll find a way out of here!"
    // "talkred_2"
    STRC_TALKRED_2_HOPE_VICTORIA_OK, // "red" "I hope Victoria is ok..."
    STRC_TALKRED_2_DOESNT_HANDLE_SUPRISES, // "red" "She doesn't handle surprises very well..."
    // "talkred_3"
    STRC_TALKRED_3_DONT_KNOW_HOW, // "red" "I don't know how we're going to get this ship working again!"
    STRC_TALKRED_3_VERDIGRIS_WOULD_KNOW, // "red" "Chief Verdigris would know what to do..."
    // "talkred_4"
    STRC_TALKRED_4_WHAT_CAUSED_CRASH, // "red" "I wonder what caused the ship to crash here?"
    STRC_TALKRED_4_SHAME_NO_PROFESSOR, // "red" "It's the shame the Professor isn't here, huh? I'm sure he could work it out!"
    // "talkred_5"
    STRC_TALKRED_5_GREAT_TO_BE_BACK, // "red" "It's great to be back!"
    STRC_TALKRED_5_CANT_WAIT_FIND_CREW, // "red" "I can't wait to help you find the rest of the crew!"
    STRC_TALKRED_5_LIKE_OLD_TIMES, // "red" "It'll be like old times, huh, Captain?"
    // "talkred_6"
    STRC_TALKRED_6_GOOD_TO_HAVE_VICTORIA, // "red" "It's good to have Victoria back with us."
    STRC_TALKRED_6_SHE_SEEMS_HAPPY, // "red" "She really seems happy to get back to work in her lab!"
    // "talkred_7"
    STRC_TALKRED_7_SAW_VERDIGRIS, // "red" "I think I saw Verdigris working on the outside of the ship!"
    // "talkred_8"
    STRC_TALKRED_8_FOUND_VITELLARY, // "red" "You found Professor Vitellary! All right!"
    STRC_TALKRED_8_INTERFERENCE_THING, // "red" "We'll have this interference thing worked out in no time now!"
    // "talkred_9"
    STRC_TALKRED_9_OTHER_DIMENSION, // "red" "That other dimension was really strange, wasn't it?"
    STRC_TALKRED_9_WHAT_CAUSED_TELE_THERE, // "red" "I wonder what caused the teleporter to send us there?"
    // "talkred_10"
    STRC_TALKRED_10_HEYA_CAPTAIN, // "red" "Heya Captain!"
    STRC_TALKRED_10_LOOKS_DANGEROUS, // "red" "This way looks a little dangerous..."
    // "talkred_11"
    STRC_TALKRED_11_IM_HELPING, // "red" "I'm helping!"
    // "talkred_12"
    STRC_TALKRED_12_HEY_CAPTAIN, // "red" "Hey Captain!"
    STRC_TALKRED_12_FOUND_WARP_SIGNATURE, // "red" "I found something interesting around here - the same warp signature I saw when I landed!"
    STRC_TALKRED_12_SOMEONE_NEARBY, // "red" "Someone from the ship must be nearby..."
    // "talkred_13"
    STRC_TALKRED_13_DIMENSION_EXCITING, // "red" "This dimension is pretty exciting, isn't it?"
    STRC_TALKRED_13_WONDER_WHAT_FIND, // "red" "I wonder what we'll find?"
    // "talkblue_1"
    STRC_TALKBLUE_1_SIGNS_OF_VITELLARY, // "blue" "Any signs of Professor Vitellary?"
    STRC_TALKBLUE_1_NOT_YET, // "player" "Sorry, not yet..."
    STRC_TALKBLUE_1_HOPE_HES_OK, // "blue" "I hope he's ok..."
    // "talkblue_2"
    STRC_TALKBLUE_2_THANKS_FOR_SAVING, // "blue" "Thanks so much for saving me, Captain!"
    // "talkblue_3"
    STRC_TALKBLUE_3_GLAD_TO_BE_BACK, // "blue" "I'm so glad to be back!"
    STRC_TALKBLUE_3_LAB_WAS_SCARY, // "blue" "That lab was so dark and scary! I didn't like it at all..."
    // "talkblue_4"
    STRC_TALKBLUE_4_VITELLARYS_BACK, // "blue" "Vitellary's back? I knew you'd find him!"
    STRC_TALKBLUE_4_ADMIT_WAS_WORRIED, // "blue" "I mean, I admit I was very worried that you wouldn't..."
    STRC_TALKBLUE_4_MIGHTVE_HAPPENED, // "blue" "or that something might have happened to him..."
    STRC_TALKBLUE_4_SNIFF, // "blue" "sniff..."
    STRC_TALKBLUE_4_HES_OK, // "player" "Doctor Victoria? He's ok!"
    STRC_TALKBLUE_4_WHAT_IF_HE_WASNT, // "blue" "Oh! Sorry! I was just thinking about what if he wasn't?"
    STRC_TALKBLUE_4_THANK_YOU, // "blue" "Thank you, Captain!"
    // "talkblue_5"
    STRC_TALKBLUE_5_FOUND_VERMILION, // "blue" "You found Vermilion! Great!"
    STRC_TALKBLUE_5_WISH_HE_WASNT_RECKLESS, // "blue" "I wish he wasn't so reckless!"
    STRC_TALKBLUE_5_GET_HIMSELF_TROUBLE, // "blue" "He'll get himself into trouble..."
    // "talkblue_6"
    STRC_TALKBLUE_6_VERDIGRIS_OK, // "blue" "Verdigris is ok! Violet will be so happy!"
    STRC_TALKBLUE_6_IM_HAPPY, // "blue" "I'm happy!"
    STRC_TALKBLUE_6_WAS_WORRIED, // "blue" "Though I was very worried..."
    // "talkblue_7"
    STRC_TALKBLUE_7_WHY_TELE_SCARY_DIMENSION, // "blue" "Why did the teleporter send us to that scary dimension?"
    STRC_TALKBLUE_7_WHAT_HAPPENED, // "blue" "What happened?"
    STRC_TALKBLUE_7_DONT_KNOW, // "player" "I don't know, Doctor..."
    STRC_TALKBLUE_7_WHY, // "blue" "Why?"
    // "talkblue_8"
    STRC_TALKBLUE_8_HEYA_CAPTAIN, // "blue" "Heya Captain!"
    STRC_TALKBLUE_8_FIND_SHINY_THINGS, // "blue" "Are you going to try and find the rest of these shiny things?"
    // "talkblue_trinket1"
    STRC_TALKBLUE_TRINKET1_FOUND_THIS, // "blue" "Hey Captain, I found this in that lab..."
    STRC_TALKBLUE_TRINKET1_ANY_IDEA_WHAT, // "blue" "Any idea what it does?"
    STRC_TALKBLUE_TRINKET1_DONT_KNOW, // "player" "Sorry, I don't know!"
    STRC_TALKBLUE_TRINKET1_SEEM_IMPORTANT, // "player" "They seem important, though..."
    STRC_TALKBLUE_TRINKET1_FIND_ALL, // "player" "Maybe something will happen if we find them all?"
    // "talkblue_trinket2"
    STRC_TALKBLUE_TRINKET2_LOOK_WORKING_ON, // "blue" "Captain! Come have a look at what I've been working on!"
    STRC_TALKBLUE_TRINKET2_ENERGY_READING, // "blue" "It looks like these shiny things are giving off a strange energy reading!"
    STRC_TALKBLUE_TRINKET2_ANALYSED, // "blue" "So I analysed it..."
    // "talkblue_trinket3"
    STRC_TALKBLUE_TRINKET3_LOOK_WORKING_ON, // "blue" "Captain! Come have a look at what I've been working on!"
    STRC_TALKBLUE_TRINKET3_FOUND_THIS, // "blue" "I found this in that lab..."
    STRC_TALKBLUE_TRINKET3_ENERGY_READING, // "blue" "It seemed to be giving off a weird energy reading..."
    STRC_TALKBLUE_TRINKET3_ANALYSED, // "blue" "So I analysed it..."
    // "talkblue_trinket4"
    STRC_TALKBLUE_TRINKET4_ABLE_FIND_MORE, // "blue" "...and I was able to find more of them with the ship's scanner!"
    STRC_TALKBLUE_TRINKET4_FIND_REST, // "blue" "If you get a chance, it might be worth finding the rest of them!"
    STRC_TALKBLUE_TRINKET4_DONT_DANGER, // "blue" "Don't put yourself in any danger, though!"
    // "talkblue_trinket5"
    STRC_TALKBLUE_TRINKET5_FOUND_ALL, // "blue" "...but it looks like you've already found all of them in this dimension!"
    STRC_TALKBLUE_TRINKET5_OH_REALLY, // "player" "Oh? Really?"
    STRC_TALKBLUE_TRINKET5_WELL_DONE, // "blue" "Yeah, well done! That can't have been easy!"
    // "talkblue_trinket6"
    STRC_TALKBLUE_TRINKET6_THEYRE_RELATED, // "blue" "...and they're related. They're all a part of something bigger!"
    STRC_TALKBLUE_TRINKET6_OH_REALLY, // "player" "Oh? Really?"
    STRC_TALKBLUE_TRINKET6_SEEM_TO_BE_20, // "blue" "Yeah! There seem to be twenty variations of the fundamental energy signature..."
    STRC_TALKBLUE_TRINKET6_WAIT, // "blue" "Wait..."
    STRC_TALKBLUE_TRINKET6_FOUND_ALL, // "blue" "Does that mean you've found all of them?"
    // "talkyellow_1"
    STRC_TALKYELLOW_1_DISCOVERIES, // "yellow" "I'm making some fascinating discoveries, captain!"
    // "talkyellow_2"
    STRC_TALKYELLOW_2_NOT_LIKE_ANY_DIMENSION, // "yellow" "This isn't like any other dimension we've been to, Captain."
    STRC_TALKYELLOW_2_SOMETHING_STRANGE, // "yellow" "There's something strange about this place..."
    // "talkyellow_3"
    STRC_TALKYELLOW_3_DIMENSION_WRAPS, // "yellow" "Captain, have you noticed that this dimension seems to wrap around?"
    STRC_TALKYELLOW_3_ITS_STRANGE, // "player" "Yeah, it's strange..."
    STRC_TALKYELLOW_3_STABILITY_PROBLEMS, // "yellow" "It looks like this dimension is having the same stability problems as our own!"
    STRC_TALKYELLOW_3_HOPE_NOT_CAUSING, // "yellow" "I hope we're not the ones causing it..."
    STRC_TALKYELLOW_3_THINK_WE_MIGHT_BE, // "player" "What? Do you think we might be?"
    STRC_TALKYELLOW_3_NO_UNLIKELY, // "yellow" "No no... that's very unlikely, really..."
    // "talkyellow_4"
    STRC_TALKYELLOW_4_EXPERIMENTING, // "yellow" "My guess is that whoever used to live here was experimenting with ways to stop the dimension from collapsing."
    STRC_TALKYELLOW_4_EXPLAIN_WRAPPED, // "yellow" "It would explain why they've wrapped the edges..."
    STRC_TALKYELLOW_4_CAUSING_INTERFERENCE, // "yellow" "Hey, maybe that's what's causing the interference?"
    // "talkyellow_5"
    STRC_TALKYELLOW_5_WHO_LIVED_HERE, // "yellow" "I wonder where the people who used to live here have gone?"
    // "talkyellow_6"
    STRC_TALKYELLOW_6_NO_CONINCIDENCE, // "yellow" "I think it's no coincidence that the teleporter was drawn to that dimension..."
    STRC_TALKYELLOW_6_SOMETHING_THERE, // "yellow" "There's something there. I think it might be causing the interference that's stopping us from leaving..."
    // "talkyellow_7"
    STRC_TALKYELLOW_7_GLAD_VERDIGRIS_ALRIGHT, // "yellow" "I'm glad Verdigris is alright."
    STRC_TALKYELLOW_7_EASIER_FIND_WAY_OUT, // "yellow" "It'll be a lot easier to find some way out of here now that we can get the ship working again!"
    // "talkyellow_8"
    STRC_TALKYELLOW_8_FOUND_VICTORIA, // "yellow" "Ah, you've found Doctor Victoria? Excellent!"
    STRC_TALKYELLOW_8_HAVE_QUESTIONS, // "yellow" "I have lots of questions for her!"
    // "talkyellow_9"
    STRC_TALKYELLOW_9_TRAPPED_TUNNEL, // "yellow" "Vermilion says that he was trapped in some sort of tunnel?"
    STRC_TALKYELLOW_9_GOING_GOING, // "player" "Yeah, it just seemed to keep going and going..."
    STRC_TALKYELLOW_9_INTERESTING, // "yellow" "Interesting... I wonder why it was built?"
    // "talkyellow_10"
    STRC_TALKYELLOW_10_GOOD_TO_BE_BACK, // "yellow" "It's good to be back!"
    STRC_TALKYELLOW_10_WORK_CATCH_UP, // "yellow" "I've got so much work to catch up on..."
    // "talkyellow_11"
    STRC_TALKYELLOW_11_DANGEROUS_STAY, // "yellow" "I know it's probably a little dangerous to stay here now that this dimension is collapsing..."
    STRC_TALKYELLOW_11_RARE_INTERESTING, // "yellow" "...but it's so rare to find somewhere this interesting!"
    STRC_TALKYELLOW_11_FIND_ANSWERS, // "yellow" "Maybe we'll find the answers to our own problems here?"
    // "talkyellow_trinket1"
    STRC_TALKYELLOW_TRINKET1_GIVE_TO_YOU, // "yellow" "Captain! I've been meaning to give this to you..."
    STRC_TALKYELLOW_TRINKET1_WHERE_FIND, // "player" "Professor! Where did you find this?"
    STRC_TALKYELLOW_TRINKET1_LYING_AROUND, // "yellow" "Oh, it was just lying around that space station."
    STRC_TALKYELLOW_TRINKET1_VICTORIA_NOT_HERE, // "yellow" "It's a pity Doctor Victoria isn't here, she loves studying that sort of thing..."
    STRC_TALKYELLOW_TRINKET1_ANY_IDEA_WHAT, // "player" "Any idea what it does?"
    STRC_TALKYELLOW_TRINKET1_ENERGY_READING, // "yellow" "Nope! But it is giving off a strange energy reading..."
    // "talkyellow_trinket2"
    STRC_TALKYELLOW_TRINKET2_FIND_MORE, // "yellow" "...so I used the ship's scanner to find more of them!"
    STRC_TALKYELLOW_TRINKET2_DONT_DISTRACT, // "yellow" "...Please don't let them distract you from finding Victoria, though!"
    STRC_TALKYELLOW_TRINKET2_HOPE_SHES_OK, // "yellow" "I hope she's ok..."
    // "talkyellow_trinket3"
    STRC_TALKYELLOW_TRINKET3_CANT_DETECT_MORE, // "yellow" "Can't seem to detect any more of them nearby, though."
    STRC_TALKYELLOW_TRINKET3_FOUND_ALL, // "yellow" "Maybe you've found them all?"
    // "finallevel_teleporter"
    STRC_FINALLEVEL_TELE_WELCOME_BACK, // "purple" "Welcome back!"
    STRC_FINALLEVEL_TELE_DOTDOTDOT, // "purple" "..."
    STRC_FINALLEVEL_TELE_WHERES_VIRIDIAN, // "purple" "Um, where's Captain Viridian?"
    STRC_FINALLEVEL_TELE_HELLO, // "player" "... Hello?"
    STRC_FINALLEVEL_TELE_ANYONE_THERE, // "player" "Is anyone there?"
    // "terminal_finallevel"
    STRC_TERMINAL_FINALLEVEL_STABILITY_GENERATOR, /* "gray" "* DIMENSIONAL STABILITY GENERATOR *

    [ Currently Generating ]
    Maximum Stability

    [ Status ]
    Online

    READY _" */
    STRC_TERMINAL_FINALLEVEL_CAUSING_INTERFERENCE, // "cyan" "Aha! This must be what's causing the interference!"
    STRC_TERMINAL_FINALLEVEL_TURN_IT_OFF, // "cyan" "I wonder if I can turn it off?"
    STRC_TERMINAL_FINALLEVEL_WARNING_YOU_SURE, // "gray" "WARNING: Disabling the Dimensional Stability Generator may lead to instability! Are you sure you want to do this?"
    STRC_TERMINAL_FINALLEVEL_YES, // "cyan" "Yes!" case="1"
    STRC_TERMINAL_FINALLEVEL_SERIOUSLY_THINK, /* "gray" "Seriously! The whole dimension could collapse! Just think about this for a minute!

    Are you really sure you want to do this?" */
    STRC_TERMINAL_FINALLEVEL_YES2, // "cyan" "Yes!" case="2"
    // "finalterminal_finish"
    STRC_FINALTERMINAL_FINISH_WARNING_OFFLINE, /* "gray" "-= WARNING =-

    DIMENSIONAL STABILISER OFFLINE" */
    STRC_FINALTERMINAL_FINISH_UH_OH, // "cyan" "Uh oh..."
    // "gamecomplete"
    STRC_GAMECOMPLETE_ANY_MOMENT, // "yellow" "Any moment now..."
    // "gamecomplete_ending"
    STRC_GAMECOMPLETE_END_HELLO, // "player" "Hello!"
    STRC_GAMECOMPLETE_END_PURPLE_CAPTAIN, // "purple" "Captain!" case="1"
    STRC_GAMECOMPLETE_END_YELLOW_CAPTAIN, // "yellow" "Captain!" case="2"
    STRC_GAMECOMPLETE_END_RED_CAPTAIN, // "red" "Captain!" case="3"
    STRC_GAMECOMPLETE_END_GREEN_CAPTAIN, // "green" "Captain!" case="4"
    STRC_GAMECOMPLETE_END_BLUE_CAPTAIN, // "blue" "Captain!" case="5"
    STRC_GAMECOMPLETE_END_YOURE_ALRIGHT, // "blue" "You're alright!"
    STRC_GAMECOMPLETE_END_KNEW_YOUD_BE_OK, // "blue" "I knew you'd be ok!"
    STRC_GAMECOMPLETE_END_WORRIED_DIDNT_COME, // "purple" "We were very worried when you didn't come back..."
    STRC_GAMECOMPLETE_END_TURNED_OFF_SOURCE, // "green" "...but when you turned off the source of the interference..."
    STRC_GAMECOMPLETE_END_FIND_YOU_SCANNERS, // "yellow" "...we were able to find you with the ship's scanners..."
    STRC_GAMECOMPLETE_END_TELEPORT_YOU, // "red" "...and teleport you back on board!"
    STRC_GAMECOMPLETE_END_WAS_LUCKY, // "player" "That was lucky!"
    STRC_GAMECOMPLETE_END_THANKS_GUYS, // "player" "Thanks guys!"
    STRC_GAMECOMPLETE_END_DESTABILISE, // "yellow" "...it looks like this dimension is starting to destabilise, just like our own..."
    STRC_GAMECOMPLETE_END_EXPLORE_A_LITTLE, // "red" "...we can stay and explore for a little longer, but..."
    STRC_GAMECOMPLETE_END_COLLAPSE_COMPLETELY, // "yellow" "...eventually, it'll collapse completely."
    STRC_GAMECOMPLETE_END_HOW_LONG, // "green" "There's no telling exactly how long we have here. But the ship's fixed, so..."
    STRC_GAMECOMPLETE_END_WE_CAN_GO_HOME, // "blue" "...as soon as we're ready, we can go home!"
    STRC_GAMECOMPLETE_END_WHAT_NOW_CAPTAIN, // "purple" "What now, Captain?"
    STRC_GAMECOMPLETE_END_SAVE_THIS_DIMENSION, // "player" "Let's find a way to save this dimension!"
    STRC_GAMECOMPLETE_END_SAVE_HOME_DIMENSION, // "player" "And a way to save our home dimension too!"
    STRC_GAMECOMPLETE_END_ANSWER_OUT_THERE, // "player" "The answer is out there, somewhere!"
    STRC_GAMECOMPLETE_END_LETS_GO, // "player" "Let's go!"
    // "startepilogue"
    STRC_STARTEPILOGUE_FOUND_ALL, // "blue" "Wow! You found all of them!"
    STRC_STARTEPILOGUE_REALLY_GREAT, // "player" "Really? Great!"
    STRC_STARTEPILOGUE_RUN_SOME_TESTS, // "blue" "I'll run some tests and see if I can work out what they're for..."
    STRC_STARTEPILOGUE_DIDNT_SOUND_GOOD, // "player" "That... that didn't sound good..."
    STRC_STARTEPILOGUE_RUN, // "blue" "Run!"
    STRC_STARTEPILOGUE_OH_NO, // "player" "Oh no!"
    STRC_STARTEPILOGUE_NOT_AGAIN, // "red" "Not again!"
    STRC_STARTEPILOGUE_ITS_STOPPED, // "player" "Wait! It's stopped!"
    STRC_STARTEPILOGUE_WHERE_STORING_SHINY, // "purple" "This is where we were storing those shiny things? What happened?"
    STRC_STARTEPILOGUE_PLAYING_AND, // "player" "We were just playing with them, and..."
    STRC_STARTEPILOGUE_EXPLODED, // "player" "...they suddenly exploded!"
    STRC_STARTEPILOGUE_IS_THAT_TELE, // "blue" "But look what they made! Is that a teleporter?"
    STRC_STARTEPILOGUE_THINK_SO, // "yellow" "I think so, but..."
    STRC_STARTEPILOGUE_NEVER_SEEN_LIKE_THAT, // "yellow" "I've never seen a teleporter like that before..."
    STRC_STARTEPILOGUE_INVESTIGATE, // "red" "We should investigate!"
    STRC_STARTEPILOGUE_WHAT_THINK_CAPTAIN, // "purple" "What do you think, Captain?"
    STRC_STARTEPILOGUE_FIND_WHERE_LEADS, // "purple" "Should we find out where it leads?"
    STRC_STARTEPILOGUE_LETS_GO, // "player" "Let's go!"
    STRC_STARTEPILOGUE_OH_NO_WERE_TRAPPED, // "blue" "Oh no! We're trapped!"
    STRC_STARTEPILOGUE_OH_DEAR, // "yellow" "Oh dear..."
    STRC_STARTEPILOGUE_HOW_GET_OUT, // "player" "Hmm... how should we get out of this?"
    STRC_STARTEPILOGUE_PLAYER_COMBINE, // "player" "COMBINE!" case="1"
    STRC_STARTEPILOGUE_PURPLE_COMBINE, // "purple" "COMBINE!" case="2"
    STRC_STARTEPILOGUE_YELLOW_COMBINE, // "yellow" "COMBINE!" case="3"
    STRC_STARTEPILOGUE_RED_COMBINE, // "red" "COMBINE!" case="4"
    STRC_STARTEPILOGUE_GREEN_COMBINE, // "green" "COMBINE!" case="5"
    STRC_STARTEPILOGUE_BLUE_COMBINE, // "blue" "COMBINE!" case="6"
    STRC_STARTEPILOGUE_COULD_HAVE_WARPED, // "purple" "Or, you know... we could have just warped back to the ship..."
    STRC_STARTEPILOGUE_WOW_WHAT_THIS, // "green" "Wow! What is this?"
    STRC_STARTEPILOGUE_ANOTHER_LAB, // "yellow" "It looks like another laboratory!"
    STRC_STARTEPILOGUE_LOOK_AROUND, // "red" "Let's have a look around!"
    // "talkpurple_9"
    STRC_TALKPURPLE_9_LOOK_THIS_RESEARCH, // "purple" "Look at all this research! This is going to be a big help back home!"
    // "talkgreen_11"
    STRC_TALKGREEN_11_WONDER_ABANDONED, // "green" "I wonder why they abandoned this dimension? They were so close to working out how to fix it..."
    STRC_TALKGREEN_11_FIX_FOR_THEM, // "green" "Maybe we can fix it for them? Maybe they'll come back?"
    // "talkblue_9"
    STRC_TALKBLUE_9_LAB_AMAZING, // "blue" "This lab is amazing! The scientists who worked here know a lot more about warp technology than we do!"
    // "talkyellow_12"
    STRC_TALKYELLOW_12_CAPTAIN_SEEN_THIS, // "yellow" "Captain! Have you seen this?"
    STRC_TALKYELLOW_12_STABILISE_OUR_DIMENSION, // "yellow" "With their research and ours, we should be able to stabilise our own dimension!"
    STRC_TALKYELLOW_12_WERE_SAVED, // "yellow" "We're saved!"
    // "talkred_14" explanation="super gravitron (difficult minigame)">
    STRC_TALKRED_14_LOOK_WHAT_I_FOUND, // "red" "Look what I found!"
    STRC_TALKRED_14_ITS_HARD, // "red" "It's pretty hard, I can only last for about 10 seconds..."
    // "terminal_jukebox"
    STRC_TERMINAL_JUKEBOX_EXPLANATION, /* "gray" "-= JUKEBOX =-

    Songs will continue to play until you leave the ship.

    Collect trinkets to unlock new songs!" */
    // "terminal_jukeunlock1"
    STRC_TERMINAL_JUKEUNLOCK1_PUSHING_ONWARDS, /* "gray" "NEXT UNLOCK:
    5 Trinkets

    Pushing Onwards" */
    // "terminal_jukeunlock2"
    STRC_TERMINAL_JUKEUNLOCK2_POSITIVE_FORCE, /* "gray" "NEXT UNLOCK:
    8 Trinkets

    Positive Force" */
    // "terminal_jukeunlock3"
    STRC_TERMINAL_JUKEUNLOCK3_PRESENTING_VVVVVV, /* "gray" "NEXT UNLOCK:
    10 Trinkets

    Presenting VVVVVV" */
    // "terminal_jukeunlock4"
    STRC_TERMINAL_JUKEUNLOCK4_POTENTIAL_FOR_ANYTHING, /* "gray" "NEXT UNLOCK:
    12 Trinkets

    Potential for Anything" */
    // "terminal_jukeunlock41"
    STRC_TERMINAL_JUKEUNLOCK41_PRESSURE_COOKER, /* "gray" "NEXT UNLOCK:
    14 Trinkets

    Pressure Cooker" */
    // "terminal_jukeunlock5"
    STRC_TERMINAL_JUKEUNLOCK5_PREDESTINED_FATE, /* "gray" "NEXT UNLOCK:
    16 Trinkets

    Predestined Fate" */
    // "terminal_jukeunlock6"
    STRC_TERMINAL_JUKEUNLOCK6_POPULAR_POTPOURRI, /* "gray" "NEXT UNLOCK:
    18 Trinkets

    Popular Potpourri" */
    // "terminal_jukeunlock7"
    STRC_TERMINAL_JUKEUNLOCK7_PIPE_DREAM, /* "gray" "NEXT UNLOCK:
    20 Trinkets

    Pipe Dream" */
    // "terminal_station_1"
    STRC_TERMINAL_STATION_1_PERSONAL_LOG, // "gray" "-= PERSONAL LOG =-"
    STRC_TERMINAL_STATION_1_EVERYONE_EVACUATED, // "gray" "Almost everyone has been evacuated from the space station now. The rest of us are leaving in a couple of days, once our research has been completed."
    // "terminal_station_2"
    STRC_TERMINAL_STATION_2_RESEARCH_NOTES, // "gray" "-= Research Notes =-"
    STRC_TERMINAL_STATION_2_EVERYTHING_COLLAPSES, // "gray" "...everything collapses, eventually. It's the way of the universe."
    // "terminal_station_3"
    STRC_TERMINAL_STATION_3_GENERATOR_AFFECTING, // "gray" "I wonder if the generator we set up in the polar dimension is what's affecting our teleporters?"
    STRC_TERMINAL_STATION_3_JUST_A_GLITCH, // "gray" "No, it's probably just a glitch."
    // "terminal_station_4" explanation="a trinket that's difficult to get">
    STRC_TERMINAL_STATION_4_PERSONAL_LOG, // "gray" "-= PERSONAL LOG =-"
    STRC_TERMINAL_STATION_4_NOBODY_WILL_GET_THIS, // "gray" "Hah! Nobody will ever get this one."
    // "terminal_warp_1"
    STRC_TERMINAL_WARP_1_CHASED_BY_AVOID, // "gray" "...The other day I was chased down a hallway by a giant cube with the word AVOID on it."
    STRC_TERMINAL_WARP_1_SECURITY_MEASURES, // "gray" "These security measures go too far!"
    // "terminal_warp_2"
    STRC_TERMINAL_WARP_2_PRIVATE_LAB, // "gray" "The only way into my private lab anymore is by teleporter."
    STRC_TERMINAL_WARP_2_MADE_IT_DIFFICULT, // "gray" "I've made sure that it's difficult for unauthorised personnel to gain access."
    // "terminal_outside_1"
    STRC_TERMINAL_OUTSIDE_1_RESEARCH_NOTES, // "gray" "-= Research Notes =-"
    STRC_TERMINAL_OUTSIDE_1_FIRST_BREAKTHROUGH, // "gray" "... our first breakthrough was the creation of the inversion plane, which creates a mirrored dimension beyond a given event horizon ..."
    // "terminal_outside_2"
    STRC_TERMINAL_OUTSIDE_2_RESEARCH_NOTES, // "gray" "-= Research Notes =-"
    STRC_TERMINAL_OUTSIDE_2_INFINITE_TUNNEL, // "gray" "...with just a small modification to the usual parameters, we were able to stabilise an infinite tunnel!"
    // "terminal_outside_3"
    STRC_TERMINAL_OUTSIDE_3_RESEARCH_NOTES, // "gray" "-= Research Notes =-"
    STRC_TERMINAL_OUTSIDE_3_FEEDBACK_LOOP, // "gray" "... the final step in creating the dimensional stabiliser was to create a feedback loop ..."
    // "terminal_outside_4"
    STRC_TERMINAL_OUTSIDE_4_RESEARCH_NOTES, // "gray" "-= Research Notes =-"
    STRC_TERMINAL_OUTSIDE_4_COLLAPSE_INEVITABLE, // "gray" "...despite our best efforts, the dimensional stabiliser won't hold out forever. Its collapse is inevitable..."
    STRC_TERMINAL_OUTSIDE_4_HUH_NOT_THIS_DIMENSION, // "cyan" "Huh? These coordinates aren't even in this dimension!"
    // "terminal_outside_5"
    STRC_TERMINAL_OUTSIDE_5_PERSONAL_LOG, // "gray" "-= Personal Log =-"
    STRC_TERMINAL_OUTSIDE_5_SEALED_RESEARCH, // "gray" "... I've had to seal off access to most of our research. Who knows what could happen if it fell into the wrong hands? ..."
    // "terminal_outside_6"
    STRC_TERMINAL_OUTSIDE_6_RESEARCH_NOTES, // "gray" "-= Research Notes =-"
    STRC_TERMINAL_OUTSIDE_6_CONTROL_CENTER, // "gray" "... access to the control center is still possible through the main atmospheric filters ..."
    // "terminal_lab_1"
    STRC_TERMINAL_LAB_1_BALANCING_FORCE, // "gray" "... it turns out the key to stabilising this dimension was to create a balancing force outside of it!"
    STRC_TERMINAL_LAB_1_TEMPORARY_SOLUTION, // "gray" "Though it looks like that's just a temporary solution, at best."
    STRC_TERMINAL_LAB_1_SOMETHING_PERMANENT, // "gray" "I've been working on something more permanent, but it seems it's going to be too late..."
    // "terminal_lab_2"
    STRC_TERMINAL_LAB_2_SYNTAX_ERROR, // "gray" "?SYNTAX  ERROR"
    // "terminal_letsgo"
    STRC_TERMINAL_LETSGO_SHIP_IS_FIXED, // "player" "Now that the ship is fixed, we can leave anytime we want!"
    STRC_TERMINAL_LETSGO_AGREED_EXPLORING, // "player" "We've all agreed to keep exploring this dimension, though."
    STRC_TERMINAL_LETSGO_WHAT_WELL_FIND, // "player" "Who knows what we'll find?"
    // "terminal_radio"
    STRC_TERMINAL_RADIO_BROADCASTING, /* "gray" "-= SHIP RADIO =-

    [ Status ]
    Broadcasting" */
    // "terminal_secretlab"
    STRC_TERMINAL_SECRETLAB_WARNING_ENTERTAINMENT, /* "gray" "-= WARNING =-

    The Super-Gravitron is intended for entertainment purposes only." */
    STRC_TERMINAL_SECRETLAB_NAUGHTY_CORNER, // "gray" "Anyone found using the Super Gravitron for educational purposes may be asked to stand in the naughty corner."
    // "terminal_shipcomputer"
    STRC_TERMINAL_SHIPCPU_SUMMARY, /* "gray" "-= D.S.S. SOULEYE =-

    Ship Navigation Controls" */
    STRC_TERMINAL_SHIPCPU_ERROR_INTERFERENCE, // "gray" "Error! Error! Cannot isolate dimensional coordinates! Interference detected!"
    // "alreadyvisited"
    STRC_ALREADYVISITED_THIS, // "cyan" "...oh, I've already found this."
    // "disableaccessibility"
    STRC_DISABLEACCESSIBILITY_SUPERGRAVITRON, // "gray" "Please disable invincibility and/or slowdown before entering the Super Gravitron."

    STRC_ID_COUNT
};



#endif /* LOCALIZATION_IDS_H */
