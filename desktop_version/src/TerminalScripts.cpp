#include "Script.h"

#ifdef __NDS__
#include "LocalizationIDs.h"
#endif

#include <SDL.h>

void scriptclass::loadother(const char* t)
{
    //loads script name t into the array
    if (SDL_strcmp(t, "terminal_station_1") == 0)
    {
        static const char* lines[] = {
        "cutscene()",
        "untilbars()",

        "squeak(terminal)",
        "text(gray,0,60,1)",
        IDC("        -= PERSONAL LOG =-         ", STRC_TERMINAL_STATION_1_PERSONAL_LOG),
        "position(centerx)",
        "backgroundtext",
        "flipme",
        "speak",

        "text(gray,0,120,6)",
        IDC(" Almost everyone has been    ", STRC_TERMINAL_STATION_1_EVERYONE_EVACUATED),
        NUL(" evacuated from the space    "),
        NUL(" station now. The rest of us "),
        NUL(" are leaving in a couple of  "),
        NUL(" days, once our research has "),
        NUL(" been completed.             "),
        "position(center)",
        "speak",

        "endtext",

        "endcutscene()",
        "untilbars()",
        };
        filllines(lines);
    }
    else if (SDL_strcmp(t, "alreadyvisited") == 0)
    {
        static const char* lines[] = {
        "squeak(player)",
        "text(cyan,0,0,1)",
        IDC("...oh, I've already found this.", STRC_ALREADYVISITED_THIS),
        "position(player,above)",
        "speak_active",
        "endtext",

        "endcutscene()",
        "untilbars()",
        };
        filllines(lines);
    }
    else if (SDL_strcmp(t, "terminal_outside_1") == 0)
    {
        static const char* lines[] = {
        "cutscene()",
        "untilbars()",

        "squeak(terminal)",
        "text(gray,0,60,1)",
        IDC("      -= Research Notes =-       ", STRC_TERMINAL_OUTSIDE_1_RESEARCH_NOTES),
        "position(centerx)",
        "backgroundtext",
        "flipme",
        "speak",

        "text(gray,0,114,5)",
        IDC(" ... our first breakthrough was ", STRC_TERMINAL_OUTSIDE_1_FIRST_BREAKTHROUGH),
        NUL(" the creation of the inversion  "),
        NUL(" plane, which creates a         "),
        NUL(" mirrored dimension beyond a   "),
        NUL(" given event horizon ...       "),
        "position(center)",
        "speak",

        "endtextfast",
        "delay(10)",

        "ifexplored(2,16,alreadyvisited)",

        "gamemode(teleporter)",
        "delay(20)",

        "squeak(terminal)",
        "showcoordinates(2,16)",
        "delay(10)",
        "hidecoordinates(2,16)",
        "delay(10)",
        "showcoordinates(2,16)",
        "delay(10)",
        "hidecoordinates(2,16)",
        "delay(10)",
        "showcoordinates(2,16)",
        "delay(45)",

        "gamemode(game)",
        "delay(20)",

        "endcutscene()",
        "untilbars()",
        };
        filllines(lines);
    }
    else if (SDL_strcmp(t, "terminal_outside_2") == 0)
    {
        static const char* lines[] = {
        "cutscene()",
        "untilbars()",

        "squeak(terminal)",
        "text(gray,0,60,1)",
        IDC("      -= Research Notes =-       ", STRC_TERMINAL_OUTSIDE_2_RESEARCH_NOTES),
        "position(centerx)",
        "backgroundtext",
        "flipme",
        "speak",

        "text(gray,0,114,3)",
        IDC("...with just a small modification to", STRC_TERMINAL_OUTSIDE_2_INFINITE_TUNNEL),
        NUL("the usual parameters, we were able  "),
        NUL("to stabilise an infinite tunnel!    "),
        "position(center)",
        "speak",

        "endtextfast",
        "delay(10)",

        "ifexplored(8,9,alreadyvisited)",

        "gamemode(teleporter)",
        "delay(20)",

        "squeak(terminal)",
        "showcoordinates(8,9)",
        "delay(10)",
        "hidecoordinates(8,9)",
        "delay(10)",
        "showcoordinates(8,9)",
        "delay(10)",
        "hidecoordinates(8,9)",
        "delay(10)",
        "showcoordinates(8,9)",
        "delay(45)",

        "gamemode(game)",
        "delay(20)",

        "endcutscene()",
        "untilbars()",
        };
        filllines(lines);
    }
    else if (SDL_strcmp(t, "terminal_outside_3") == 0)
    {
        static const char* lines[] = {
        "cutscene()",
        "untilbars()",

        "squeak(terminal)",
        "text(gray,0,60,1)",
        IDC("      -= Research Notes =-       ", STRC_TERMINAL_OUTSIDE_3_RESEARCH_NOTES),
        "position(centerx)",
        "backgroundtext",
        "flipme",
        "speak",

        "text(gray,0,114,3)",
        IDC(" ... the final step in creating ", STRC_TERMINAL_OUTSIDE_3_FEEDBACK_LOOP),
        NUL(" the dimensional stabiliser was "),
        NUL(" to create a feedback loop ... "),
        "position(center)",
        "speak",

        "endtextfast",
        "delay(10)",

        "ifexplored(14,1,alreadyvisited)",

        "gamemode(teleporter)",
        "delay(20)",

        "squeak(terminal)",
        "showcoordinates(14,1)",
        "delay(10)",
        "hidecoordinates(14,1)",
        "delay(10)",
        "showcoordinates(14,1)",
        "delay(10)",
        "hidecoordinates(14,1)",
        "delay(10)",
        "showcoordinates(14,1)",
        "delay(45)",

        "gamemode(game)",
        "delay(20)",

        "endcutscene()",
        "untilbars()",
        };
        filllines(lines);
    }
    else if (SDL_strcmp(t, "terminal_outside_4") == 0)
    {
        static const char* lines[] = {
        "cutscene()",
        "untilbars()",

        "squeak(terminal)",
        "text(gray,0,60,1)",
        IDC("      -= Research Notes =-       ", STRC_TERMINAL_OUTSIDE_4_RESEARCH_NOTES),
        "position(centerx)",
        "backgroundtext",
        "flipme",
        "speak",

        "text(gray,0,114,4)",
        IDC(" ...despite our best efforts, ", STRC_TERMINAL_OUTSIDE_4_COLLAPSE_INEVITABLE),
        NUL(" the dimensional stabiliser   "),
        NUL(" won't hold out forever. Its  "),
        NUL(" collapse is inevitable...    "),
        "position(center)",
        "speak",

        "endtextfast",
        "delay(10)",

        "squeak(player)",
        "text(cyan,0,0,2)",
        IDC("Huh? These coordinates aren't", STRC_TERMINAL_OUTSIDE_4_HUH_NOT_THIS_DIMENSION),
        NUL("even in this dimension!"),
        "position(player,above)",
        "speak_active",
        "endtext",

        "endcutscene()",
        "untilbars()",
        };
        filllines(lines);
    }
    else if (SDL_strcmp(t, "terminal_outside_5") == 0)
    {
        static const char* lines[] = {
        "cutscene()",
        "untilbars()",

        "squeak(terminal)",
        "text(gray,0,60,1)",
        IDC("     -= Personal Log =-      ", STRC_TERMINAL_OUTSIDE_5_PERSONAL_LOG),
        "position(centerx)",
        "backgroundtext",
        "flipme",
        "speak",

        "text(gray,0,114,5)",
        IDC(" ... I've had to seal off ", STRC_TERMINAL_OUTSIDE_5_SEALED_RESEARCH),
        NUL("   access to most of our "),
        NUL(" research. Who knows what "),
        NUL(" could happen if it fell  "),
        NUL(" into the wrong hands? ...  "),
        "position(center)",
        "speak",

        "endtextfast",
        "delay(10)",

        "gamemode(teleporter)",
        "delay(20)",

        "squeak(terminal)",
        "showsecretlab()",
        "delay(10)",
        "hidesecretlab()",
        "delay(10)",
        "showsecretlab()",
        "delay(10)",
        "hidesecretlab()",
        "delay(10)",
        "showsecretlab()",
        "delay(45)",

        "gamemode(game)",
        "delay(20)",

        "endcutscene()",
        "untilbars()",
        };
        filllines(lines);
    }
    else if (SDL_strcmp(t, "terminal_outside_6") == 0)
    {
        static const char* lines[] = {
        "cutscene()",
        "untilbars()",

        "squeak(terminal)",
        "text(gray,0,60,1)",
        IDC("      -= Research Notes =-       ", STRC_TERMINAL_OUTSIDE_6_RESEARCH_NOTES),
        "position(centerx)",
        "backgroundtext",
        "flipme",
        "speak",

        "text(gray,0,114,3)",
        IDC("... access to the control center", STRC_TERMINAL_OUTSIDE_6_CONTROL_CENTER),
        NUL("is still possible through the   "),
        NUL("main atmospheric filters ...    "),
        "position(center)",
        "speak",

        "endtextfast",
        "delay(10)",

        "ifexplored(12,14,alreadyvisited)",

        "gamemode(teleporter)",
        "delay(20)",

        "squeak(terminal)",
        "showcoordinates(12,14)",
        "delay(10)",
        "hidecoordinates(12,14)",
        "delay(10)",
        "showcoordinates(12,14)",
        "delay(10)",
        "hidecoordinates(12,14)",
        "delay(10)",
        "showcoordinates(12,14)",
        "delay(45)",

        "gamemode(game)",
        "delay(20)",

        "endcutscene()",
        "untilbars()",
        };
        filllines(lines);
    }
    else if (SDL_strcmp(t, "terminal_finallevel") == 0)
    {
        static const char* lines[] = {
        "cutscene()",
        "untilbars()",

        "squeak(terminal)",
        "text(gray,0,114,9)",
        IDC("* DIMENSIONAL STABILITY GENERATOR *", STRC_TERMINAL_FINALLEVEL_STABILITY_GENERATOR),
        NUL(""),
        NUL("     [ Currently Generating ]      "),
        NUL("        Maximum Stability    "),
        NUL(""),
        NUL("            [ Status ]"),
        NUL("              Online"),
        NUL(""),
        NUL("READY _"),
        "position(center)",
        "speak_active",

        "endtextfast",
        "delay(10)",

        "squeak(player)",
        "text(cyan,0,0,2)",
        IDC("Aha! This must be what's" , STRC_TERMINAL_FINALLEVEL_CAUSING_INTERFERENCE),
        NUL("causing the interference!"),
        "position(player,above)",
        "speak_active",

        "squeak(player)",
        "text(cyan,0,0,1)",
        IDC("I wonder if I can turn it off?", STRC_TERMINAL_FINALLEVEL_TURN_IT_OFF),
        "position(player,above)",
        "speak_active",

        "squeak(terminal)",
        "text(gray,0,114,4)",
        IDC("WARNING: Disabling the Dimensional", STRC_TERMINAL_FINALLEVEL_WARNING_YOU_SURE),
        NUL("Stability Generator may lead to"),
        NUL("instability! Are you sure you want"),
        NUL("to do this?"),
        "position(center)",
        "speak_active",

        "squeak(player)",
        "textcase(1)",
        "text(cyan,0,0,1)",
        IDC("Yes!", STRC_TERMINAL_FINALLEVEL_YES),
        "position(player,above)",
        "speak_active",

        "squeak(terminal)",
        "text(gray,0,114,6)",
        IDC("Seriously! The whole dimension", STRC_TERMINAL_FINALLEVEL_SERIOUSLY_THINK),
        NUL("could collapse! Just think about"),
        NUL("this for a minute!"),
        NUL(""),
        NUL("Are you really sure you want"),
        NUL("to do this?"),
        "position(center)",
        "speak_active",

        "squeak(player)",
        "textcase(2)",
        "text(cyan,0,0,1)",
        IDC("Yes!", STRC_TERMINAL_FINALLEVEL_YES2),
        "position(player,above)",
        "speak_active",

        "endtext",

        "stopmusic",
        "gamestate(200)",
        };
        filllines(lines);
    }
    else if (SDL_strcmp(t, "finalterminal_finish") == 0)
    {


        static const char* lines[] = {
        //"delay(15)",    "flash(5)", "shake(20)", "playef(9)",

        "text(gray,0,114,3)",
        IDC("          -= WARNING =-         ", STRC_FINALTERMINAL_FINISH_WARNING_OFFLINE),
        NUL(""),
        NUL(" DIMENSIONAL STABILISER OFFLINE "),
        "position(center)",
        "speak_active",
        "endtext",

        "squeak(cry)",
        "changemood(player,1)",
        "text(cyan,0,0,1)",
        IDC("Uh oh...", STRC_FINALTERMINAL_FINISH_UH_OH),
        "position(player,above)",
        "speak_active",
        "endtext",

        "play(2)",
        "changemood(player,0)",

        "endcutscene()",
        "untilbars()",
        };
        filllines(lines);
    }
    else if (SDL_strcmp(t, "terminal_station_2") == 0)
    {
        static const char* lines[] = {
        "cutscene()",
        "untilbars()",

        "squeak(terminal)",
        "text(gray,0,60,1)",
        IDC("      -= Research Notes =-       ", STRC_TERMINAL_STATION_2_RESEARCH_NOTES),
        "position(centerx)",
        "backgroundtext",
        "flipme",
        "speak",

        "text(gray,0,114,3)",
        IDC(" ...everything collapses,  ", STRC_TERMINAL_STATION_2_EVERYTHING_COLLAPSES),
        NUL(" eventually. It's the way  "),
        NUL("    of the universe.       "),
        "position(center)",
        "speak",

        "endtextfast",

        "endcutscene()",
        "untilbars()",
        };
        filllines(lines);
    }
    else if (SDL_strcmp(t, "terminal_station_3") == 0)
    {
        static const char* lines[] = {
        "cutscene()",
        "untilbars()",

        "squeak(terminal)",
        "text(gray,0,114,3)",
        IDC("I wonder if the generator we set", STRC_TERMINAL_STATION_3_GENERATOR_AFFECTING),
        NUL("up in the polar dimension is"),
        NUL("what's affecting our teleporters?"),
        "position(center)",
        "speak_active",

        "squeak(terminal)",
        "text(gray,0,114,1)",
        IDC("No, it's probably just a glitch.", STRC_TERMINAL_STATION_3_JUST_A_GLITCH),
        "position(center)",
        "speak_active",

        "endtext",

        "endcutscene()",
        "untilbars()",
        };
        filllines(lines);
    }
    else if (SDL_strcmp(t, "terminal_station_4") == 0)
    {
        static const char* lines[] = {
        "cutscene()",
        "untilbars()",

        "squeak(terminal)",
        "text(gray,0,60,1)",
        IDC("        -= PERSONAL LOG =-         ", STRC_TERMINAL_STATION_4_PERSONAL_LOG),
        "position(centerx)",
        "backgroundtext",
        "flipme",
        "speak",

        "text(gray,0,114,2)",
        IDC(" Hah! Nobody will ever ", STRC_TERMINAL_STATION_4_NOBODY_WILL_GET_THIS),
        NUL(" get this one. "),
        "position(center)",
        "speak",

        "endtextfast",

        "endcutscene()",
        "untilbars()",
        };
        filllines(lines);
    }
    else if (SDL_strcmp(t, "terminal_warp_1") == 0)
    {
        static const char* lines[] = {
        "cutscene()",
        "untilbars()",

        "squeak(terminal)",
        "text(gray,0,114,3)",
        IDC("...The other day I was chased", STRC_TERMINAL_WARP_1_CHASED_BY_AVOID),
        NUL("down a hallway by a giant cube"),
        NUL("with the word AVOID on it."),
        "position(center)",
        "speak_active",

        "squeak(terminal)",
        "text(gray,0,114,1)",
        IDC("These security measures go too far!", STRC_TERMINAL_WARP_1_SECURITY_MEASURES),
        "position(center)",
        "speak_active",

        "endtext",

        "endcutscene()",
        "untilbars()",
        };
        filllines(lines);
    }
    else if (SDL_strcmp(t, "terminal_warp_2") == 0)
    {
        static const char* lines[] = {
        "cutscene()",
        "untilbars()",

        "squeak(terminal)",
        "text(gray,0,114,2)",
        IDC("The only way into my private lab", STRC_TERMINAL_WARP_2_PRIVATE_LAB),
        NUL("anymore is by teleporter."),
        "position(center)",
        "speak_active",

        "squeak(terminal)",
        "text(gray,0,114,3)",
        IDC("I've made sure that it's", STRC_TERMINAL_WARP_2_MADE_IT_DIFFICULT),
        NUL("difficult for unauthorised"),
        NUL("personnel to gain access."),
        "position(center)",
        "speak_active",

        "endtext",

        "endcutscene()",
        "untilbars()",
        };
        filllines(lines);
    }
    else if (SDL_strcmp(t, "terminal_lab_1") == 0)
    {
        static const char* lines[] = {
        "cutscene()",
        "untilbars()",

        "squeak(terminal)",
        "text(gray,0,114,4)",
        IDC("... it turns out the key to", STRC_TERMINAL_LAB_1_BALANCING_FORCE),
        NUL("stabilising this dimension was"),
        NUL("to create a balancing force"),
        NUL("outside of it!"),
        "position(center)",
        "speak_active",

        "squeak(terminal)",
        "text(gray,0,114,2)",
        IDC("Though it looks like that's just", STRC_TERMINAL_LAB_1_TEMPORARY_SOLUTION),
        NUL("a temporary solution, at best."),
        "position(center)",
        "speak_active",

        "squeak(terminal)",
        "text(gray,0,114,4)",
        IDC("I've been working on", STRC_TERMINAL_LAB_1_SOMETHING_PERMANENT),
        NUL("something more permanent,"),
        NUL("but it seems it's going"),
        NUL("to be too late..."),
        "position(center)",
        "speak_active",

        "endtext",

        "endcutscene()",
        "untilbars()",
        };
        filllines(lines);
    }
    else if (SDL_strcmp(t, "terminal_lab_2") == 0)
    {
        static const char* lines[] = {
        "cutscene()",
        "untilbars()",

        "squeak(terminal)",
        "text(gray,0,114,1)",
        IDC("?SYNTAX  ERROR", STRC_TERMINAL_LAB_2_SYNTAX_ERROR),
        "position(center)",
        "speak_active",

        "endtext",

        "endcutscene()",
        "untilbars()",
        };
        filllines(lines);
    }
    else if (SDL_strcmp(t, "terminal_secretlab") == 0)
    {
        static const char* lines[] = {
        "cutscene()",
        "untilbars()",

        "squeak(terminal)",
        "text(gray,0,114,4)",
        IDC("         -= WARNING =-", STRC_TERMINAL_SECRETLAB_WARNING_ENTERTAINMENT),
        NUL(""),
        NUL(" The Super-Gravitron is intended  "),
        NUL(" for entertainment purposes only. "),
        "position(center)",
        "speak_active",

        "squeak(terminal)",
        "text(gray,0,114,4)",
        IDC("Anyone found using the Super", STRC_TERMINAL_SECRETLAB_NAUGHTY_CORNER),
        NUL("Gravitron for educational"),
        NUL("purposes may be asked to"),
        NUL("stand in the naughty corner."),
        "position(center)",
        "speak_active",

        "endtext",

        "endcutscene()",
        "untilbars()",
        };
        filllines(lines);
    }
    else if (SDL_strcmp(t, "terminal_shipcomputer") == 0)
    {
        static const char* lines[] = {
        "cutscene()",
        "untilbars()",

        "squeak(terminal)",
        "text(gray,0,114,3)",
        IDC("   -= D.S.S. SOULEYE =-   ", STRC_TERMINAL_SHIPCPU_SUMMARY),
        NUL(""),
        NUL(" Ship Navigation Controls "),
        "position(center)",
        "speak_active",

        "ifflag(67,terminal_letsgo)",

        "squeak(terminal)",
        "text(gray,0,114,3)",
        IDC("Error! Error! Cannot isolate", STRC_TERMINAL_SHIPCPU_ERROR_INTERFERENCE),
        NUL("dimensional coordinates!"),
        NUL("Interference detected!"),
        "position(center)",
        "speak_active",
        "endtext",

        "endcutscene()",
        "untilbars()",
        };
        filllines(lines);
    }
    else if (SDL_strcmp(t, "terminal_letsgo") == 0)
    {
        static const char* lines[] = {
        "squeak(player)",
        "text(player,0,0,2)",
        IDC("Now that the ship is fixed,", STRC_TERMINAL_LETSGO_SHIP_IS_FIXED),
        NUL("we can leave anytime we want!"),
        "position(player,above)",
        "speak_active",

        "squeak(player)",
        "text(player,0,0,3)",
        IDC("We've all agreed to", STRC_TERMINAL_LETSGO_AGREED_EXPLORING),
        NUL("keep exploring this"),
        NUL("dimension, though."),
        "position(player,above)",
        "speak_active",

        "squeak(player)",
        "text(player,0,0,1)",
        IDC("Who knows what we'll find?", STRC_TERMINAL_LETSGO_WHAT_WELL_FIND),
        "position(player,above)",
        "speak_active",
        "endtext",

        "endcutscene()",
        "untilbars()",
        };
        filllines(lines);
    }
    else if (SDL_strcmp(t, "terminal_radio") == 0)
    {
        static const char* lines[] = {
        "cutscene()",
        "untilbars()",

        "squeak(terminal)",
        "text(gray,0,114,4)",
        IDC("  -= SHIP RADIO =-  ", STRC_TERMINAL_RADIO_BROADCASTING),
        NUL(""),
        NUL("     [ Status ]"),
        NUL("    Broadcasting"),
        "position(center)",
        "speak_active",

        "endtext",

        "endcutscene()",
        "untilbars()",
        };
        filllines(lines);
    }
    else if (SDL_strcmp(t, "terminal_jukebox") == 0)
    {
        static const char* lines[] = {
        "cutscene()",
        "untilbars()",

        "squeak(terminal)",
        "text(gray,0,114,7)",
        IDC("          -= JUKEBOX =-       ", STRC_TERMINAL_JUKEBOX_EXPLANATION),
        NUL(""),
        NUL("   Songs will continue to play   "),
        NUL("   until you leave the ship."),
        NUL(""),
        NUL("      Collect trinkets to"),
        NUL("       unlock new songs!"),
        "position(center)",
        "speak_active",

        "endtext",

        "iftrinketsless(5,terminal_jukeunlock1)",
        "iftrinketsless(8,terminal_jukeunlock2)",
        "iftrinketsless(10,terminal_jukeunlock3)",
        "iftrinketsless(12,terminal_jukeunlock4)",
        "iftrinketsless(14,terminal_jukeunlock41)",
        "iftrinketsless(16,terminal_jukeunlock5)",
        "iftrinketsless(18,terminal_jukeunlock6)",
        "iftrinketsless(20,terminal_jukeunlock7)",

        "endcutscene()",
        "untilbars()",
        };
        filllines(lines);
    }
    else if (SDL_strcmp(t, "terminal_jukeunlock1") == 0)
    {
        static const char* lines[] = {
        "squeak(terminal)",
        "text(gray,0,114,4)",
        IDC(" NEXT UNLOCK:    ", STRC_TERMINAL_JUKEUNLOCK1_PUSHING_ONWARDS),
        NUL(" 5 Trinkets"),
        NUL(""),
        NUL(" Pushing Onwards "),
        "position(center)",
        "speak_active",
        "endtext",

        "endcutscene()",
        "untilbars()",
        };
        filllines(lines);
    }
    else if (SDL_strcmp(t, "terminal_jukeunlock2") == 0)
    {
        static const char* lines[] = {
        "squeak(terminal)",
        "text(gray,0,114,4)",
        IDC(" NEXT UNLOCK:    ", STRC_TERMINAL_JUKEUNLOCK2_POSITIVE_FORCE),
        NUL(" 8 Trinkets"),
        NUL(""),
        NUL(" Positive Force "),
        "position(center)",
        "speak_active",
        "endtext",

        "endcutscene()",
        "untilbars()",
        };
        filllines(lines);
    }
    else if (SDL_strcmp(t, "terminal_jukeunlock3") == 0)
    {
        static const char* lines[] = {
        "squeak(terminal)",
        "text(gray,0,114,4)",
        IDC(" NEXT UNLOCK:    ", STRC_TERMINAL_JUKEUNLOCK3_PRESENTING_VVVVVV),
        NUL(" 10 Trinkets"),
        NUL(""),
        NUL(" Presenting VVVVVV "),
        "position(center)",
        "speak_active",
        "endtext",

        "endcutscene()",
        "untilbars()",
        };
        filllines(lines);
    }
    else if (SDL_strcmp(t, "terminal_jukeunlock4") == 0)
    {
        static const char* lines[] = {
        "squeak(terminal)",
        "text(gray,0,114,4)",
        IDC(" NEXT UNLOCK:    ", STRC_TERMINAL_JUKEUNLOCK4_POTENTIAL_FOR_ANYTHING),
        NUL(" 12 Trinkets"),
        NUL(""),
        NUL(" Potential for Anything "),
        "position(center)",
        "speak_active",
        "endtext",

        "endcutscene()",
        "untilbars()",
        };
        filllines(lines);
    }
    else if (SDL_strcmp(t, "terminal_jukeunlock41") == 0)
    {
        static const char* lines[] = {
        "squeak(terminal)",
        "text(gray,0,114,4)",
        IDC(" NEXT UNLOCK:    ", STRC_TERMINAL_JUKEUNLOCK41_PRESSURE_COOKER),
        NUL(" 14 Trinkets"),
        NUL(""),
        NUL(" Pressure Cooker "),
        "position(center)",
        "speak_active",
        "endtext",

        "endcutscene()",
        "untilbars()",
        };
        filllines(lines);
    }
    else if (SDL_strcmp(t, "terminal_jukeunlock5") == 0)
    {
        static const char* lines[] = {
        "squeak(terminal)",
        "text(gray,0,114,4)",
        IDC(" NEXT UNLOCK:    ", STRC_TERMINAL_JUKEUNLOCK5_PREDESTINED_FATE),
        NUL(" 16 Trinkets"),
        NUL(""),
        NUL(" Predestined Fate "),
        "position(center)",
        "speak_active",
        "endtext",

        "endcutscene()",
        "untilbars()",
        };
        filllines(lines);
    }
    else if (SDL_strcmp(t, "terminal_jukeunlock6") == 0)
    {
        static const char* lines[] = {
        "squeak(terminal)",
        "text(gray,0,114,4)",
        IDC(" NEXT UNLOCK:    ", STRC_TERMINAL_JUKEUNLOCK6_POPULAR_POTPOURRI),
        NUL(" 18 Trinkets"),
        NUL(""),
        NUL(" Popular Potpourri "),
        "position(center)",
        "speak_active",
        "endtext",

        "endcutscene()",
        "untilbars()",
        };
        filllines(lines);
    }
    else if (SDL_strcmp(t, "terminal_jukeunlock7") == 0)
    {
        static const char* lines[] = {
        "squeak(terminal)",
        "text(gray,0,114,4)",
        IDC(" NEXT UNLOCK:    ", STRC_TERMINAL_JUKEUNLOCK7_PIPE_DREAM),
        NUL(" 20 Trinkets"),
        NUL(""),
        NUL(" Pipe Dream "),
        "position(center)",
        "speak_active",
        "endtext",

        "endcutscene()",
        "untilbars()",
        };
        filllines(lines);
    }
    else if (SDL_strcmp(t, "terminal_juke1") == 0)
    {
        static const char* lines[] = {
        "play(4)",
        "squeak(terminal)",
        "jukebox(1)",
        };
        filllines(lines);
    }
    else if (SDL_strcmp(t, "terminal_juke2") == 0)
    {
        static const char* lines[] = {
        "play(1)",
        "squeak(terminal)",
        "jukebox(2)",
        };
        filllines(lines);
    }
    else if (SDL_strcmp(t, "terminal_juke3") == 0)
    {
        static const char* lines[] = {
        "play(2)",
        "squeak(terminal)",
        "jukebox(3)",
        };
        filllines(lines);
    }
    else if (SDL_strcmp(t, "terminal_juke4") == 0)
    {
        static const char* lines[] = {
        "play(6)",
        "squeak(terminal)",
        "jukebox(4)",
        };
        filllines(lines);
    }
    else if (SDL_strcmp(t, "terminal_juke5") == 0)
    {
        static const char* lines[] = {
        "play(3)",
        "squeak(terminal)",
        "jukebox(5)",
        };
        filllines(lines);
    }
    else if (SDL_strcmp(t, "terminal_juke6") == 0)
    {
        static const char* lines[] = {
        "play(8)",
        "squeak(terminal)",
        "jukebox(6)",
        };
        filllines(lines);
    }
    else if (SDL_strcmp(t, "terminal_juke7") == 0)
    {
        static const char* lines[] = {
        "play(11)",
        "squeak(terminal)",
        "jukebox(7)",
        };
        filllines(lines);
    }
    else if (SDL_strcmp(t, "terminal_juke8") == 0)
    {
        static const char* lines[] = {
        "play(10)",
        "squeak(terminal)",
        "jukebox(8)",
        };
        filllines(lines);
    }
    else if (SDL_strcmp(t, "terminal_juke9") == 0)
    {
        static const char* lines[] = {
        "play(12)",
        "squeak(terminal)",
        "jukebox(9)",
        };
        filllines(lines);
    }
    else if (SDL_strcmp(t, "terminal_juke10") == 0)
    {
        static const char* lines[] = {
        "play(9)",
        "squeak(terminal)",
        "jukebox(10)",
        };
        filllines(lines);
    }
}
