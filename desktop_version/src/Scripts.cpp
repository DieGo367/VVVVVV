#include "Script.h"
#ifdef __NDS__
#include "LocalizationIDs.h"
#endif

#include <SDL.h>

bool scriptclass::load(const std::string& name)
{
    //loads script name t into the array
    position = 0;
    commands.clear();
    scriptname = name;
    running = true;

    const char* t = name.c_str();

    if (SDL_strncmp(t, "custom_", 7) == 0)
    {
        return loadcustom(name);
    }
    else if (SDL_strcmp(t, "intro") == 0)
    {
        static const char* lines[] = {
        "ifskip(quickstart)",
        //"createcrewman(232,113,cyan,0,faceright)",
        "createcrewman(96,177,green,0,faceright)",
        "createcrewman(122,177,purple,0,faceleft)",
        "fadein()",
        "untilfade()",
        "delay(90)",

        "flash(5)",
        "shake(20)",
        "playef(9)",
        "musicfadeout()",
        "changemood(player,1)",
        "delay(15)",
        "squeak(player)",
        "text(cyan,0,0,1)",
        IDC("Uh oh...", STRC_INTRO_UH_OH),
        "position(player,above)",
        //"backgroundtext",
        "speak_active",

        "squeak(purple)",
        "changeai(purple,followposition,175)",
        "text(purple,145,150,1)",
        IDC("Is everything ok?", STRC_INTRO_IS_EVERYTHING_OK),
        //"position(purple,above)",
        //"backgroundtext",
        "speak_active",

        "squeak(player)",
        "walk(left,2)",
        "text(cyan,0,0,2)",
        IDC("No! We've hit some", STRC_INTRO_HIT_INTERFERENCE),
        NUL("kind of interference..."),
        "position(player,above)",
        //"backgroundtext",
        "speak_active",

        //"delay(30)",
        "endtext",

        "flash(5)",
        "shake(50)",
        "playef(9)",
        "changemood(green,1)",
        "changemood(purple,1)",
        "alarmon",

        "changedir(player,1)",
        "delay(30)",
        "endtext",

        "squeak(player)",
        "text(cyan,0,0,2)",
        IDC("Something's wrong! We're", STRC_INTRO_SOMETHING_WRONG),
        NUL("going to crash!"),
        "position(player,above)",
        //"backgroundtext",
        "speak_active",
        //"delay(100)",

        "endtext",

        "flash(5)",
        "shake(50)",
        "playef(9)",
        "changeai(green,followposition,-60)",
        "changeai(purple,followposition,-60)",
        "squeak(player)",
        "text(cyan,70,140,1)",
        IDC("Evacuate!", STRC_INTRO_EVACUATE),
        "backgroundtext",
        "speak_active",
        "walk(left,35)",

        "endtextfast",

        //Ok, next room!

        "flash(5)",
        "shake(50)",
        "playef(9)",
        "gotoroom(3,10)",
        "gotoposition(310,177,0)",
        "createcrewman(208,177,green,1,followposition,120)",
        "createcrewman(240,177,purple,1,followposition,120)",
        "createcrewman(10,177,blue,1,followposition,180)",

        "squeak(blue)",
        "text(blue,80,150,1)",
        IDC("Oh no!", STRC_INTRO_OH_NO),
        "backgroundtext",
        "speak_active",
        "walk(left,20)",

        "endtextfast",

        //and the next!
        "flash(5)",
        "shake(50)",
        "playef(9)",
        "gotoroom(3,11)",
        "gotoposition(140,0,0)",

        "createcrewman(90,105,green,1,followblue)",
        "createcrewman(125,105,purple,1,followgreen)",
        "createcrewman(55,105,blue,1,followposition,-200)",

        "createcrewman(120,177,yellow,1,followposition,-200)",
        "createcrewman(240,177,red,1,faceleft)",

        "delay(5)",
        "changeai(red,followposition,-200)",

        "squeak(red)",
        "text(red,100,150,1)",
        IDC("Everyone off the ship!", STRC_INTRO_OFF_THE_SHIP),
        "backgroundtext",
        "speak_active",

        "walk(left,25)",

        "endtextfast",

        //final room:
        "flash(5)",
        "shake(80)",
        "playef(9)",
        "gotoroom(2,11)",
        "gotoposition(265,153,0)",

        "createcrewman(130,153,blue,1,faceleft)",
        "createcrewman(155,153,green,1,faceleft)",
        "createcrewman(180,153,purple,1,faceleft)",
        "createcrewman(205,153,yellow,1,faceleft)",
        "createcrewman(230,153,red,1,faceleft)",


        "squeak(yellow)",
        "text(yellow,0,0,1)",
        IDC("This shouldn't be happening!", STRC_INTRO_SHOULDNT_HAPPEN),
        "position(yellow,below)",
        "backgroundtext",
        "speak_active",

        "activateteleporter()",

        "delay(10)",
        "changecolour(blue,teleporter)",
        "delay(10)",
        "changecolour(green,teleporter)",
        "delay(10)",
        "changecolour(purple,teleporter)",
        "delay(10)",
        "changecolour(yellow,teleporter)",
        "delay(10)",
        "changecolour(red,teleporter)",
        "delay(10)",

        //and teleport!
        "endtext",
        "alarmoff",
        "flash(5)",
        "shake(20)",
        "playef(10)",
        "blackout()",
        "changemood(player,0)",
        "changedir(player,1)",

        "delay(100)",
        "blackon()",
        "shake(20)",
        "playef(10)",

        //Finally, appear at the start of the game:
        "gotoroom(13,5)",
        "gotoposition(80,96,0)",
        "walk(right,20)",
        //"delay(45)",

        "squeak(player)",
        "text(cyan,0,0,1)",
        IDC("Phew! That was scary!", STRC_INTRO_PHEW_SCARY),
        "position(player,above)",
        "speak_active",

        "squeak(player)",
        "text(cyan,0,0,2)",
        IDC("At least we all", STRC_INTRO_WE_ALL_ESCAPED_RIGHT),
        NUL("escaped, right guys?"),
        "position(player,above)",
        "speak_active",

        "endtext",

        "delay(45)",
        "walk(left,3)",
        "delay(45)",
        "setcheckpoint()",

        "squeak(player)",
        "text(cyan,0,0,1)",
        IDC("...guys?", STRC_INTRO_GUYS),
        "position(player,above)",
        "speak_active",

        "endtext",

        "delay(25)",
        "changemood(player,1)",
        "squeak(cry)",
        "delay(25)",

        "play(1)",
        "endcutscene()",
        "untilbars()",

        "hideship()",

        "gamestate(4)",
        };
        filllines(lines);
    }
    else if (SDL_strcmp(t, "quickstart") == 0)
    {
        //Finally, appear at the start of the game:
        static const char* lines[] = {
        "gotoroom(13,5)",
        "gotoposition(80,96,0)",
        "walk(right,17)",
        "fadein()",

        "setcheckpoint()",

        "play(1)",
        "endcutscene()",
        "untilbars()",

        "hideship()",
        };
        filllines(lines);
    }
    else if (SDL_strcmp(t, "firststeps") == 0)
    {
        static const char* lines[] = {
        "cutscene()",
        "untilbars()",

        "squeak(player)",
        "text(cyan,0,0,2)",
        IDC("I wonder why the ship", STRC_FIRSTSTEPS_WHY_TELE_ALONE),
        NUL("teleported me here alone?"),
        "position(player,above)",
        "speak_active",

        "squeak(cry)",
        "text(cyan,0,0,2)",
        IDC("I hope everyone else", STRC_FIRSTSTEPS_HOPE_EVERYONE_OK),
        NUL("got out ok..."),
        "position(player,above)",
        "speak_active",

        "endtext",

        "endcutscene()",
        "untilbars()",
        };
        filllines(lines);
    }
    else if (SDL_strcmp(t, "trenchwarfare") == 0)
    {
        static const char* lines[] = {
        "cutscene()",
        "untilbars()",

        "iftrinkets(1,newtrenchwarfare)",

        "squeak(player)",
        "text(cyan,0,0,1)",
        IDC("Ohh! I wonder what that is?", STRC_TRENCHWAREFARE_WONDER),
        "position(player,above)",
        "speak_active",

        "squeak(player)",
        "text(cyan,0,0,3)",
        IDC("I probably don't really need it,", STRC_TRENCHWAREFARE_TAKE_TO_SHIP),
        NUL("but it might be nice to take it"),
        NUL("back to the ship to study..."),
        "position(player,above)",
        "speak_active",

        "endtext",

        "endcutscene()",
        "untilbars()",
        };
        filllines(lines);
    }
    else if (SDL_strcmp(t, "newtrenchwarfare") == 0)
    {
        static const char* lines[] = {
        "squeak(player)",
        "text(cyan,0,0,2)",
        IDC("Oh! It's another one of", STRC_NEWTRENCHWARFARE_SHINY_THING),
        NUL("those shiny things!"),
        "position(player,above)",
        "speak_active",

        "squeak(player)",
        "text(cyan,0,0,3)",
        IDC("I probably don't really need it,", STRC_NEWTRENCHWARFARE_TAKE_TO_SHIP),
        NUL("but it might be nice to take it"),
        NUL("back to the ship to study..."),
        "position(player,above)",
        "speak_active",

        "endtext",

        "endcutscene()",
        "untilbars()",
        };
        filllines(lines);
    }
    else if (SDL_strcmp(t, "trinketcollector") == 0)
    {
        static const char* lines[] = {
        "cutscene()",
        "untilbars()",

        "iftrinkets(1,newtrinketcollector)",

        "squeak(player)",
        "text(cyan,0,0,3)",
        IDC("This seems like a good", STRC_TRINKETCOLLECTOR_STORE_THING),
        NUL("place to store anything"),
        NUL("I find out there..."),
        "position(player,above)",
        "speak_active",

        "squeak(player)",
        "text(cyan,0,0,3)",
        IDC("Victoria loves to study the", STRC_TRINKETCOLLECTOR_VICTORIA_STUDY),
        NUL("interesting things we find"),
        NUL("on our adventures!"),
        "position(player,above)",
        "speak_active",

        "ifcrewlost(5,new2trinketcollector)",

        "endtext",

        "endcutscene()",
        "untilbars()",
        };
        filllines(lines);
    }
    else if (SDL_strcmp(t, "newtrinketcollector") == 0)
    {
        static const char* lines[] = {
        "squeak(player)",
        "text(cyan,0,0,3)",
        IDC("This seems like a good", STRC_NEWTRINKETCOLLECTOR_STORE_SHINY),
        NUL("place to store those"),
        NUL("shiny things."),
        "position(player,above)",
        "speak_active",

        "squeak(player)",
        "text(cyan,0,0,3)",
        IDC("Victoria loves to study the", STRC_NEWTRINKETCOLLECTOR_VICTORIA_STUDY),
        NUL("interesting things we find"),
        NUL("on our adventures!"),
        "position(player,above)",
        "speak_active",

        "ifcrewlost(5,new2trinketcollector)",

        "endtext",

        "endcutscene()",
        "untilbars()",
        };
        filllines(lines);
    }
    else if (SDL_strcmp(t, "new2trinketcollector") == 0)
    {
        static const char* lines[] = {
        "squeak(cry)",
        "changemood(player,1)",
        "text(cyan,0,0,1)",
        IDC("I hope she's ok...", STRC_NEW2TRINKETCOLLECTOR_HOPE_SHES_OK),
        "position(player,above)",
        "speak_active",
        "endtext",

        "changemood(player,0)",

        "endcutscene()",
        "untilbars()",
        };
        filllines(lines);
    }
    if (SDL_strcmp(t, "communicationstation") == 0)
    {
        static const char* lines[] = {
        "ifskip(communicationstationskip)",
        "cutscene()",
        "untilbars()",
        "changemood(player,0)",

        "tofloor",
        "play(5)",
        "delay(10)",

        "squeak(player)",
        "text(cyan,0,0,1)",
        IDC("Violet! Is that you?", STRC_COMMSTATION_VIOLET_THAT_YOU),
        "position(player,above)",
        "speak_active",
        "endtext",

        "squeak(purple)",
        "text(purple,45,18,1)",
        IDC("Captain! You're ok!", STRC_COMMSTATION_CAPTAIN_YOURE_OK),
        "speak_active",

        "squeak(cry)",
        "text(purple,20,16,3)",
        IDC("Something has gone", STRC_COMMSTATION_SOMETHING_WRONG_TELE),
        NUL("horribly wrong with the"),
        NUL("ship's teleporter!"),
        "speak_active",

        "squeak(purple)",
        "text(purple,8,14,3)",
        IDC("I think everyone has been", STRC_COMMSTATION_EVERYONE_TELE_RANDOM),
        NUL("teleported away randomly!"),
        NUL("They could be anywhere!"),
        "speak_active",

        "squeak(cry)",
        "changemood(player,1)",
        "text(cyan,0,0,1)",
        IDC("Oh no!", STRC_COMMSTATION_OH_NO),
        "position(player,above)",
        "speak_active",

        "squeak(purple)",
        "text(purple,10,19,2)",
        IDC("I'm on the ship - it's damaged", STRC_COMMSTATION_SHIP_DAMAGED_INTACT),
        NUL("badly, but it's still intact!"),
        "speak_active",

        "squeak(purple)",
        "text(purple,10,15,1)",
        IDC("Where are you, Captain?", STRC_COMMSTATION_WHERE_CAPTAIN),
        "speak_active",

        "squeak(player)",
        "changemood(player,0)",
        "text(cyan,0,0,3)",
        IDC("I'm on some sort of", STRC_COMMSTATION_ON_SPACESTATION),
        NUL("space station... It"),
        NUL("seems pretty modern..."),
        "position(player,above)",
        "speak_active",

        "squeak(purple)",
        "text(purple,15,16,2)",
        IDC("There seems to be some sort of", STRC_COMMSTATION_INTERFERENCE),
        NUL("interference in this dimension..."),
        "speak_active",

        "hideteleporters()",
        "endtextfast",
        "delay(10)",

        //add map mode here and wrap up...
        "gamemode(teleporter)",
        "delay(20)",

        "squeak(purple)",
        "text(purple,25,205,2)",
        IDC("I'm broadcasting the coordinates", STRC_COMMSTATION_BROADCASTING),
        NUL("of the ship to you now."),
        "speak_active",
        "endtext",

        "squeak(terminal)",
        "showship()",
        "delay(10)",
        "hideship()",
        "delay(10)",
        "showship()",
        "delay(10)",
        "hideship()",
        "delay(10)",
        "showship()",
        "delay(20)",

        "squeak(purple)",
        "text(purple,10,200,1)",
        IDC("I can't teleport you back, but...", STRC_COMMSTATION_CANT_TELE_BACK),
        "speak_active",

        "squeak(purple)",
        "text(purple,25,195,3)",
        IDC("If YOU can find a teleporter", STRC_COMMSTATION_FIND_A_TELE),
        NUL("anywhere nearby, you should be"),
        NUL("able to teleport back to me!"),
        "speak_active",
        "endtext",

        "squeak(terminal)",
        "delay(20)",
        "showteleporters()",
        "delay(10)",
        "hideteleporters()",
        "delay(10)",
        "showteleporters()",
        "delay(10)",
        "hideteleporters()",
        "delay(10)",
        "showteleporters()",
        "delay(20)",

        "squeak(player)",
        "text(cyan,20,190,1)",
        IDC("Ok! I'll try to find one!", STRC_COMMSTATION_OK_ILL_TRY),
        "speak_active",
        "endtext",
        "delay(20)",

        "gamemode(game)",
        "delay(20)",

        "squeak(purple)",
        "text(purple,40,22,1)",
        IDC("Good luck, Captain!", STRC_COMMSTATION_GOOD_LUCK),
        "speak_active",
        "endtext",

        "squeak(purple)",
        "text(purple,10,19,2)",
        IDC("I'll keep trying to find", STRC_COMMSTATION_FIND_CREW),
        NUL("the rest of the crew..."),
        "speak_active",
        "endtext",

        "endcutscene()",
        "untilbars()",
        "play(1)",
        };
        filllines(lines);
    }
    else if (SDL_strcmp(t, "communicationstationskip") == 0)
    {
        static const char* lines[] = {
        "changemood(player,0)",

        "delay(10)",
        "endtext",
        //add map mode here and wrap up...
        "gamemode(teleporter)",
        "delay(5)",

        "squeak(terminal)",
        "showship()",
        "showteleporters()",
        "delay(10)",
        "hideship()",
        "hideteleporters()",
        "delay(10)",
        "showship()",
        "showteleporters()",
        "delay(10)",
        "hideship()",
        "hideteleporters()",
        "delay(10)",
        "showship()",
        "showteleporters()",
        "delay(20)",

        "gamemode(game)",
        };
        filllines(lines);
    }
    else if (SDL_strcmp(t, "teleporterback") == 0)
    {
        static const char* lines[] = {
        "cutscene()",
        "untilbars()",

        "squeak(player)",
        "text(cyan,0,0,1)",
        IDC("A teleporter!", STRC_TELEBACK_A_TELE),
        "position(player,above)",
        "speak_active",

        "squeak(player)",
        "text(cyan,0,0,2)",
        IDC("I can get back to the", STRC_TELEBACK_I_CAN_GET_BACK),
        NUL("ship with this!"),
        "position(player,above)",
        "speak_active",

        "endtext",

        "teleportscript(levelonecomplete)",

        "endcutscene()",
        "untilbars()",
        };
        filllines(lines);
    }
    else if (SDL_strcmp(t, "levelonecomplete") == 0)
    {
        static const char* lines[] = {
        "nocontrol()",
        "createcrewman(230,153,purple,0,faceleft)",

        "cutscene()",
        "untilbars()",

        "delay(30)",
        "rescued(purple)",

        "delay(10)",
        "gamestate(4090)",
        };
        filllines(lines);
    }
    else if (SDL_strcmp(t, "levelonecomplete_ending") == 0)
    {
        static const char* lines[] = {
        "squeak(purple)",
        "text(purple,0,0,1)",
        IDC("Captain!", STRC_LEVELCOMPLETEEND_CAPTAIN),
        "position(purple,above)",
        "speak_active",
        "endtext",
        "nocontrol()",

        "endcutscene()",
        "untilbars()",

        "gamestate(3050)",
        };
        filllines(lines);
    }
    else if (SDL_strcmp(t, "levelonecompleteskip") == 0)
    {
        static const char* lines[] = {
        "nocontrol()",
        "gamestate(3050)",
        };
        filllines(lines);
    }
    else if (SDL_strcmp(t, "bigopenworld") == 0)
    {
        static const char* lines[] = {
        "play(5)",
        "cutscene()",
        "untilbars()",

        "missing(purple)", //Set violet's rescue script to 0 to make the next bit easier

        "gotoroom(4,10)",
        "gotoposition(100,177,0)",
        "createcrewman(150,177,purple,0,faceleft)",

        //set all the crew as rescued to avoid companion issues!
        "flag(8,on)",
        "flag(9,on)",
        "flag(10,on)",
        "flag(11,on)",

        "fadein()",
        "untilfade()",

        "delay(15)",

        "squeak(player)",
        "text(player,0,0,2)",
        IDC("So, Doctor - have you any", STRC_BIGOPENWORLD_ANY_IDEA_CRASH),
        NUL("idea what caused the crash?"),
        "position(player,above)",
        "speak_active",

        "squeak(purple)",
        "text(purple,0,0,3)",
        IDC("There's some sort of bizarre", STRC_BIGOPENWORLD_BIZARRE_SIGNAL),
        NUL("signal here that's interfering"),
        NUL("with our equipment..."),
        "position(purple,above)",
        "speak_active",

        "squeak(purple)",
        "text(purple,0,0,3)",
        IDC("It caused the ship to lose", STRC_BIGOPENWORLD_QUANTUM_POSITION),
        NUL("its quantum position, collapsing"),
        NUL("us into this dimension!"),
        "position(purple,above)",
        "speak_active",

        "squeak(cry)",
        "changemood(player,1)",
        "text(player,0,0,1)",
        IDC("Oh no!", STRC_BIGOPENWORLD_OH_NO),
        "position(player,above)",
        "speak_active",

        "squeak(purple)",
        "text(purple,0,0,2)",
        IDC("But I think we should be able to fix", STRC_BIGOPENWORLD_ABLE_FIX_SHIP),
        NUL("the ship and get out of here..."),
        "position(purple,above)",
        "speak_active",

        "squeak(purple)",
        "text(purple,0,0,2)",
        IDC("... as long as we can", STRC_BIGOPENWORLD_FIND_CREW),
        NUL("find the rest of the crew."),
        "position(purple,above)",
        "speak_active",

        "endtext",

        //Cut to Red
        "fadeout()",
        "untilfade()",

        "changeplayercolour(red)",
        "gotoroom(10,4)",
        "gotoposition(200,185,0)",
        "hideplayer()",
        "createcrewman(200,185,red,1,panic)",

        "fadein()",
        "untilfade()",

        //"walk(right,10)",

        "squeak(purple)",
        "text(purple,60,40,2)",
        IDC("We really don't know anything", STRC_BIGOPENWORLD_DONT_KNOW),
        NUL("about this place..."),
        "speak_active",

        "endtext",

        "delay(15)",

        //Cut to Green
        "fadeout()",
        "untilfade()",

        "showplayer()",

        "changeplayercolour(green)",
        "gotoroom(13,0)",
        "gotoposition(143,20,0)",

        "fadein()",
        "untilfade()",


        "squeak(purple)",
        "text(purple,40,30,2)",
        IDC("Our friends could be anywhere - they", STRC_BIGOPENWORLD_FRIENDS_ANYWHERE),
        NUL("could be lost, or in danger!"),
        "speak_active",

        "endtext",

        "delay(15)",

        //Cut to Blue
        "fadeout()",
        "untilfade()",

        "changeplayercolour(blue)",
        "gotoroom(3,4)",
        "gotoposition(190,177,0)",

        "fadein()",
        "untilfade()",


        "squeak(player)",
        "text(player,10,60,1)",
        IDC("Can they teleport back here?", STRC_BIGOPENWORLD_CAN_TELE_BACK),
        "speak_active",

        "squeak(purple)",
        "text(purple,50,80,2)",
        IDC("Not unless they find some way", STRC_BIGOPENWORLD_FIND_COMM),
        NUL("to communicate with us!"),
        "speak_active",

        "squeak(purple)",
        "text(purple,30,100,3)",
        IDC("We can't pick up their signal and", STRC_BIGOPENWORLD_CANT_PICKUP_SIGNAL),
        NUL("they can't teleport here unless"),
        NUL("they know where the ship is..."),
        "speak_active",

        "endtext",

        "delay(15)",


        //Cut to Yellow
        "fadeout()",
        "untilfade()",

        "changeplayercolour(yellow)",
        "gotoroom(15,9)",
        //(6*8)-21
        "gotoposition(300,27,0)",

        "hideplayer()",
        "createcrewman(280,25,yellow,1,panic)",

        //"hascontrol()",
        //"walk(left,4)",

        "fadein()",
        "untilfade()",

        "squeak(player)",
        "text(player,25,60,1)",
        IDC("So what do we do?", STRC_BIGOPENWORLD_SO_WHAT_DO),
        "speak_active",

        "squeak(purple)",
        "text(purple,80,125,4)",
        IDC("We need to find them! Head", STRC_BIGOPENWORLD_FIND_THEM),
        NUL("out into the dimension and"),
        NUL("look for anywhere they might"),
        "have ended up...",
        "speak_active",

        "endtext",

        "delay(15)",

        //Back to ship
        "fadeout()",
        "untilfade()",
        "showplayer()",

        "flag(8,off)",
        "flag(9,off)",
        "flag(10,off)",
        "flag(11,off)",

        "changeplayercolour(cyan)",
        "changemood(player,0)",
        "gotoroom(4,10)",
        "gotoposition(90,177,0)",
        "walk(right,2)",
        "createcrewman(150,177,purple,0,faceleft)",



        "fadein()",
        "untilfade()",

        "squeak(player)",
        "text(player,0,0,1)",
        IDC("Ok! Where do we start?", STRC_BIGOPENWORLD_OK_WHERE_START),
        "position(player,above)",
        "speak_active",

        "squeak(purple)",
        "text(purple,0,0,2)",
        IDC("Well, I've been trying to find", STRC_BIGOPENWORLD_WITH_SCANNERS),
        NUL("them with the ship's scanners!"),
        "position(purple,above)",
        "speak_active",

        "squeak(purple)",
        "text(purple,0,0,2)",
        IDC("It's not working, but I did", STRC_BIGOPENWORLD_FOUND_SOMETHING),
        NUL("find something..."),
        "position(purple,above)",
        "speak_active",

        "endtext",

        "delay(15)",

        "hidecoordinates(10,4)",
        "hidecoordinates(13,0)",
        "hidecoordinates(3,4)",
        "hidecoordinates(15,9)",
        "showteleporters()",

        //Cut to map
        //add map mode here and wrap up...
        "gamemode(teleporter)",
        "delay(20)",

        "squeak(terminal)",
        "showtargets()",
        "delay(10)",
        "hidetargets()",
        "delay(10)",
        "showtargets()",
        "delay(10)",
        "hidetargets()",
        "delay(10)",
        "showtargets()",
        "delay(20)",

        "squeak(purple)",
        "text(purple,25,205,2)",
        IDC("These points show up on our scans", STRC_BIGOPENWORLD_HIGH_ENERGY),
        NUL("as having high energy patterns!"),
        "speak_active",
        "endtext",

        "squeak(purple)",
        "text(purple,35,185,4)",
        IDC("There's a good chance they're", STRC_BIGOPENWORLD_CHANCE_TELE),
        NUL("teleporters - which means"),
        NUL("they're probably built near"),
        NUL("something important..."),
        "speak_active",

        "squeak(purple)",
        "text(purple,25,205,2)",
        IDC("They could be a very good", STRC_BIGOPENWORLD_START_LOOKING),
        NUL("place to start looking."),
        "speak_active",
        "endtext",
        "delay(20)",

        "gamemode(game)",
        "delay(20)",
        //And finally, back to the ship!

        "squeak(player)",
        "text(player,0,0,2)",
        IDC("Ok! I'll head out and see", STRC_BIGOPENWORLD_ILL_HEAD_OUT),
        NUL("what I can find!"),
        "position(player,above)",
        "speak_active",

        "squeak(purple)",
        "text(purple,0,0,2)",
        IDC("I'll be right here if", STRC_BIGOPENWORLD_HERE_IF_NEED_HELP),
        NUL("you need any help!"),
        "position(purple,above)",
        "speak_active",
        "endtext",

        "rescued(purple)",
        "play(4)",

        "endcutscene()",
        "untilbars()",
        "hascontrol()",

        "createactivityzone(purple)",
        };
        filllines(lines);
    }
    else if (SDL_strcmp(t, "bigopenworldskip") == 0)
    {
        static const char* lines[] = {
        "missing(purple)",
        "gotoroom(4,10)",
        "gotoposition(100,177,0)",
        "createcrewman(150,177,purple,0,faceleft)",

        "fadein()",
        "untilfade()",

        "hidecoordinates(10,4)",
        "hidecoordinates(13,0)",
        "hidecoordinates(3,4)",
        "hidecoordinates(15,9)",
        "showteleporters()",

        //Cut to map
        //add map mode here and wrap up...
        "gamemode(teleporter)",
        "delay(20)",

        "squeak(terminal)",
        "showtargets()",
        "delay(10)",
        "hidetargets()",
        "delay(10)",
        "showtargets()",
        "delay(10)",
        "hidetargets()",
        "delay(10)",
        "showtargets()",
        "delay(20)",

        "gamemode(game)",
        "delay(20)",
        //And finally, back to the ship!

        "squeak(purple)",
        "text(purple,0,0,2)",
        IDC("I'll be right here if", STRC_BIGOPENWORLDSKIP_HERE_IF_NEED_HELP),
        NUL("you need any help!"),
        "position(purple,above)",
        "speak_active",
        "endtext",

        "rescued(purple)",
        "play(4)",

        "endcutscene()",
        "untilbars()",
        "hascontrol()",

        "createactivityzone(purple)",
        };
        filllines(lines);
    }
    else if (SDL_strcmp(t, "rescueblue") == 0)
    {
        static const char* lines[] = {
        "ifskip(skipblue)",
        "cutscene()",

        "tofloor()",
        "changeai(blue,followplayer)",
        "untilbars()",

        "rescued(blue)",

        "squeak(blue)",
        "text(blue,0,0,2)",
        IDC("Oh no! Captain! Are you", STRC_RESCUEBLUE_OH_NO_CAPTAIN),
        NUL("stuck here too?"),
        "position(blue,above)",
        "speak_active",

        "squeak(player)",
        "text(player,0,0,1)",
        IDC("It's ok - I'm here to rescue you!", STRC_RESCUEBLUE_HERE_TO_RESCUE),
        "position(player,above)",
        "speak_active",

        "squeak(player)",
        "text(player,0,0,1)",
        IDC("Let me explain everything...", STRC_RESCUEBLUE_LET_ME_EXPLAIN),
        "position(player,above)",
        "speak_active",

        "endtext",

        "fadeout()",
        "untilfade()",
        "delay(30)",
        "fadein()",
        "untilfade()",

        "squeak(cry)",
        "text(blue,0,0,2)",
        IDC("What? I didn't understand", STRC_RESCUEBLUE_WHAT),
        NUL("any of that!"),
        "position(blue,above)",
        "speak_active",

        "squeak(player)",
        "text(player,0,0,1)",
        IDC("Oh... well, don't worry.", STRC_RESCUEBLUE_DONT_WORRY),
        "position(player,above)",
        "speak_active",

        "squeak(player)",
        "text(player,0,0,2)",
        IDC("Follow me! Everything", STRC_RESCUEBLUE_FOLLOW_ME),
        NUL("will be alright!"),
        "position(player,above)",
        "speak_active",

        "squeak(blue)",
        "changemood(blue,0)",
        "text(blue,0,0,1)",
        IDC("Sniff... Really?", STRC_RESCUEBLUE_SNIFF_REALLY),
        "position(blue,above)",
        "speak_active",

        "squeak(blue)",
        "text(blue,0,0,1)",
        IDC("Ok then!", STRC_RESCUEBLUE_OK_THEN),
        "position(blue,above)",
        "speak_active",

        "endtext",

        "endcutscene()",
        "untilbars()",
        "companion(8)",
        "setcheckpoint()",
        };
        filllines(lines);
    }
    else if (SDL_strcmp(t, "skipblue") == 0)
    {
        static const char* lines[] = {
        "changeai(blue,followplayer)",
        "squeak(blue)",
        "changemood(blue,0)",
        "companion(8)",
        "rescued(blue)",
        "setcheckpoint()",
        };
        filllines(lines);
    }
    else if (SDL_strcmp(t, "rescueyellow") == 0)
    {
        static const char* lines[] = {
        "ifskip(skipyellow)",
        "cutscene()",

        "changeai(yellow,followplayer)",
        "changetile(yellow,6)",
        "untilbars()",

        "rescued(yellow)",

        "squeak(yellow)",
        "text(yellow,0,0,2)",
        IDC("Ah, Viridian! You got off", STRC_RESCUEYELLOW_AH_VIRIDIAN),
        NUL("the ship alright too? "),
        "position(yellow,above)",
        "speak_active",

        "squeak(player)",
        "text(player,0,0,2)",
        IDC("It's good to see you're", STRC_RESCUEYELLOW_GOOD_TO_SEE_YOU),
        NUL("alright, Professor!"),
        "position(player,above)",
        "speak_active",

        "squeak(yellow)",
        "text(yellow,0,0,1)",
        IDC("Is the ship ok?", STRC_RESCUEYELLOW_IS_SHIP_OK),
        "position(yellow,above)",
        "speak_active",

        "squeak(player)",
        "text(player,0,0,2)",
        IDC("It's badly damaged, but Violet's", STRC_RESCUEYELLOW_DAMAGED_VIOLET_FIXING),
        NUL("been working on fixing it."),
        "position(player,above)",
        "speak_active",

        "squeak(player)",
        "text(player,0,0,1)",
        IDC("We could really use your help...", STRC_RESCUEYELLOW_COULD_USE_YOUR_HELP),
        "position(player,above)",
        "speak_active",

        "endtext",

        "fadeout()",
        "untilfade()",
        "delay(30)",
        "fadein()",
        "untilfade()",

        "squeak(yellow)",
        "text(yellow,0,0,1)",
        IDC("Ah, of course!", STRC_RESCUEYELLOW_OF_COURSE),
        "position(yellow,above)",
        "speak_active",

        "squeak(yellow)",
        "text(yellow,0,0,4)",
        IDC("The background interference", STRC_RESCUEYELLOW_BACKGROUND_INTERFERENCE),
        NUL("in this dimension prevented"),
        NUL("the ship from finding a"),
        NUL("teleporter when we crashed!"),
        "position(yellow,above)",
        "speak_active",

        "squeak(yellow)",
        "text(yellow,0,0,2)",
        IDC("We've all been teleported", STRC_RESCUEYELLOW_TELE_DIFFERENT_LOCATIONS),
        NUL("to different locations!"),
        "position(yellow,above)",
        "speak_active",

        "squeak(player)",
        "text(player,0,0,1)",
        IDC("Er, that sounds about right!", STRC_RESCUEYELLOW_SOUNDS_RIGHT),
        "position(player,above)",
        "speak_active",

        "squeak(yellow)",
        "text(yellow,0,0,2)",
        IDC("Let's get back to", STRC_RESCUEYELLOW_BACK_TO_THE_SHIP),
        NUL("the ship, then!"),
        "position(yellow,above)",
        "speak_active",

        "squeak(yellow)",
        "text(yellow,0,0,1)",
        IDC("After you, Captain!", STRC_RESCUEYELLOW_AFTER_YOU),
        "position(yellow,above)",
        "speak_active",

        "endtext",

        "companion(7)",
        "endcutscene()",
        "untilbars()",
        };
        filllines(lines);
    }
    else if (SDL_strcmp(t, "skipyellow") == 0)
    {
        static const char* lines[] = {
        "changeai(yellow,followplayer)",
        "changetile(yellow,6)",
        "squeak(yellow)",
        "rescued(yellow)",
        "companion(7)",
        };
        filllines(lines);
    }
    else if (SDL_strcmp(t, "rescuegreen") == 0)
    {
        static const char* lines[] = {
        "ifskip(skipgreen)",
        "cutscene()",

        "tofloor()",
        "changemood(green,0)",
        "untilbars()",

        "rescued(green)",

        "squeak(green)",
        "text(green,0,0,1)",
        IDC("Captain! I've been so worried!", STRC_RESCUEGREEN_CAPTAIN_IVE_WORRIED),
        "position(green,above)",
        "speak_active",

        "squeak(player)",
        "text(player,0,0,1)",
        IDC("Chief Verdigris! You're ok!", STRC_RESCUEGREEN_VERDIGRIS_YOURE_OK),
        "position(player,above)",
        "speak_active",

        "squeak(cry)",
        "changemood(green,1)",
        "text(green,0,0,2)",
        IDC("I've been trying to get out, but", STRC_RESCUEGREEN_TRYING_GET_OUT),
        NUL("I keep going around in circles..."),
        "position(green,above)",
        "speak_active",

        "squeak(player)",
        "text(player,0,0,2)",
        IDC("I've come from the ship. I'm here", STRC_RESCUEGREEN_COME_FROM_SHIP),
        NUL("to teleport you back to it."),
        "position(player,above)",
        "speak_active",

        "squeak(green)",
        "text(green,0,0,2)",
        IDC("Is everyone else", STRC_RESCUEGREEN_IS_EVERYONE_ALRIGHT),
        NUL("alright? Is Violet..."),
        "position(green,above)",
        "speak_active",

        "squeak(player)",
        "text(player,0,0,1)",
        IDC("She's fine - she's back on the ship!", STRC_RESCUEGREEN_SHES_ON_SHIP),
        "position(player,above)",
        "speak_active",

        "squeak(green)",
        "changemood(green,0)",
        "text(green,0,0,2)",
        IDC("Oh! Great - Let's", STRC_RESCUEGREEN_GET_GOING),
        NUL("get going, then!"),
        "position(green,above)",
        "speak_active",

        "endtext",

        "companion(6)",
        "endcutscene()",
        "untilbars()",
        "changeai(green,followplayer)",
        };
        filllines(lines);
    }
    else if (SDL_strcmp(t, "skipgreen") == 0)
    {
        static const char* lines[] = {
        "changeai(green,followplayer)",
        "squeak(green)",
        "rescued(green)",
        "changemood(green,0)",
        "companion(6)",
        };
        filllines(lines);
    }
    else if (SDL_strcmp(t, "rescuered") == 0)
    {
        static const char* lines[] = {
        "ifskip(skipred)",
        "cutscene()",

        "tofloor()",
        "changemood(red,0)",
        "untilbars()",

        "rescued(red)",

        "squeak(red)",
        "text(red,0,0,1)",
        IDC("Captain!", STRC_RESCUERED_CAPTAIN),
        "position(red,above)",
        "speak_active",

        "squeak(red)",
        "text(red,0,0,3)",
        IDC("Am I ever glad to see you!", STRC_RESCUERED_GLAD_TO_SEE_YOU),
        NUL("I thought I was the only"),
        NUL("one to escape the ship..."),
        "position(red,above)",
        "speak_active",

        "squeak(player)",
        "text(player,0,0,1)",
        IDC("Vermilion! I knew you'd be ok!", STRC_RESCUERED_VERMILION_KNEW_BE_OK),
        "position(player,above)",
        "speak_active",

        "squeak(red)",
        "text(red,0,0,1)",
        IDC("So, what's the situation?", STRC_RESCUERED_WHATS_SITUATION),
        "position(red,above)",
        "speak_active",

        "endtext",

        "fadeout()",
        "untilfade()",
        "delay(30)",
        "fadein()",
        "untilfade()",

        "squeak(red)",
        "text(red,0,0,2)",
        IDC("I see! Well, we'd better", STRC_RESCUERED_I_SEE),
        NUL("get back then."),
        "position(red,above)",
        "speak_active",

        "squeak(red)",
        "text(red,0,0,2)",
        IDC("There's a teleporter", STRC_RESCUERED_THERES_TELE),
        NUL("in the next room."),
        "position(red,above)",
        "speak_active",

        "endtext",

        "companion(9)",
        "endcutscene()",
        "untilbars()",
        "changeai(red,followplayer)",
        };
        filllines(lines);
    }
    else if (SDL_strcmp(t, "skipred") == 0)
    {
        static const char* lines[] = {
        "changeai(red,followplayer)",
        "squeak(red)",
        "rescued(red)",
        "changemood(red,0)",
        "companion(9)",
        };
        filllines(lines);
    }
    else if (SDL_strcmp(t, "startexpolevel_station1") == 0)
    {
        static const char* lines[] = {
        //For the Eurogamer EXPO! Scrap later.
        "fadeout()",
        "musicfadeout()",
        "untilfade()",

        "cutscene()",
        "untilbars()",

        "resetgame",

        "gotoroom(4,10)",
        "gotoposition(232,113,0)",
        "setcheckpoint()",
        "changedir(player,1)",
        "fadein()",

        "play(5)",
        "loadscript(intro)",
        };
        filllines(lines);
    }
    else if (SDL_strcmp(t, "startexpolevel_lab") == 0)
    {
        static const char* lines[] = {
        //For the Eurogamer EXPO! Scrap later.
        "fadeout()",
        "musicfadeout()",
        "untilfade()",
        "delay(30)",

        "resetgame",

        "gotoroom(2,16)",
        "gotoposition(58,193,0)",
        "setcheckpoint()",
        "changedir(player,1)",
        "fadein()",

        "stopmusic()",
        "play(3)",
        };
        filllines(lines);
    }
    else if (SDL_strcmp(t, "startexpolevel_warp") == 0)
    {
        static const char* lines[] = {
        //For the Eurogamer EXPO! Scrap later.
        "fadeout()",
        "musicfadeout()",
        "untilfade()",
        "delay(30)",

        "resetgame",

        "gotoroom(14,1)",
        "gotoposition(45,73,0)",
        "setcheckpoint()",
        "changedir(player,1)",
        "fadein()",

        "stopmusic()",
        "play(3)",
        };
        filllines(lines);
    }
    else if (SDL_strcmp(t, "startexpolevel_tower") == 0)
    {
        static const char* lines[] = {
        //For the Eurogamer EXPO! Scrap later.
        "fadeout()",
        "musicfadeout()",
        "untilfade()",
        "delay(30)",

        "resetgame",

        "gotoroom(8,9)",
        "gotoposition(95,193,0)",
        "setcheckpoint()",
        "changedir(player,1)",
        "fadein()",

        "stopmusic()",
        "play(2)",
        };
        filllines(lines);
    }
    else if (SDL_strcmp(t, "skipint1") == 0)
    {
        static const char* lines[] = {
        "finalmode(41,56)",
        "gotoposition(52,89,0)",
        "changedir(player,1)",
        "setcheckpoint()",
        "delay(15)",

        "flash(5)",
        "shake(20)",
        "playef(9)",
        "showplayer()",
        "play(8)",

        "hascontrol()",
        "befadein()",
        };
        filllines(lines);
    }
    else if (SDL_strcmp(t, "intermission_1") == 0)
    {
        static const char* lines[] = {
        "ifskip(skipint1)",
        "finalmode(41,56)",
        "gotoposition(52,89,0)",
        "changedir(player,1)",
        "setcheckpoint()",

        "cutscene()",

        "delay(15)",

        "flash(5)",
        "shake(20)",
        "playef(9)",

        "delay(35)",

        "flash(5)",
        "shake(20)",
        "playef(9)",

        "delay(25)",

        "flash(5)",
        "shake(20)",
        "playef(10)",

        "showplayer()",
        "play(8)",

        "befadein()",

        "iflast(2,int1yellow_1)",
        "iflast(3,int1red_1)",
        "iflast(4,int1green_1)",
        "iflast(5,int1blue_1)",
        };
        filllines(lines);
    }
    else if (SDL_strcmp(t, "int1blue_1") == 0)
    {
        static const char* lines[] = {
        "delay(45)",

        "squeak(cry)",
        "textcase(1)",
        "text(blue,0,0,1)",
        IDC("Waaaa!", STRC_INT1BLUE_1_WAAAA),
        "position(blue,above)",
        "speak_active",
        "face(player,blue)",
        "face(blue,player)",

        "squeak(blue)",
        "text(blue,0,0,1)",
        IDC("Captain! Are you ok?", STRC_INT1BLUE_1_CAPTAIN_YOU_OK),
        "position(blue,above)",
        "speak_active",

        "squeak(player)",
        "text(player,0,0,2)",
        IDC("I'm ok... this...", STRC_INT1BLUE_1_IM_OK),
        NUL("this isn't the ship..."),
        "position(player,above)",
        "speak_active",

        "squeak(player)",
        "text(player,0,0,1)",
        IDC("Where are we?", STRC_INT1BLUE_1_WHERE_ARE_WE),
        "position(player,above)",
        "speak_active",

        "squeak(cry)",
        "textcase(2)",
        "text(blue,0,0,1)",
        IDC("Waaaa!", STRC_INT1BLUE_1_WAAAA2),
        "position(blue,above)",
        "speak_active",

        "squeak(player)",
        "text(player,0,0,2)",
        IDC("Something's gone wrong... We", STRC_INT1BLUE_1_GONE_WRONG),
        NUL("should look for a way back!"),
        "position(player,above)",
        "speak_active",
        "endtext",

        "telesave()",

        "endcutscene()",
        "untilbars()",
        "gamestate(14)",
        };
        filllines(lines);
    }
    else if (SDL_strcmp(t, "int1blue_2") == 0)
    {
        static const char* lines[] = {
        "cutscene()",
        "untilbars()",

        "squeak(player)",
        "text(player,0,0,1)",
        IDC("Follow me! I'll help you!", STRC_INT1BLUE_2_FOLLOW_ME),
        "position(player,above)",
        "speak_active",

        "squeak(cry)",
        "text(blue,0,0,1)",
        IDC("Promise you won't leave without me!", STRC_INT1BLUE_2_PROMISE_WONT_LEAVE),
        "position(blue,above)",
        "speak_active",

        "squeak(player)",
        "text(player,0,0,1)",
        IDC("I promise! Don't worry!", STRC_INT1BLUE_2_I_PROMISE),
        "position(player,above)",
        "speak_active",

        "endtext",

        "endcutscene()",
        "untilbars()",
        "gamestate(11)",
        };
        filllines(lines);
    }
    else if (SDL_strcmp(t, "int1blue_3") == 0)
    {
        static const char* lines[] = {
        "cutscene()",
        "untilbars()",
        "face(player,blue)",
        "face(blue,player)",

        "squeak(player)",
        "text(player,0,0,1)",
        IDC("Are you ok down there, Doctor?", STRC_INT1BLUE_3_YOU_OK_DOCTOR),
        "position(player,below)",
        "speak_active",

        "squeak(cry)",
        "text(blue,0,0,1)",
        IDC("I wanna go home!", STRC_INT1BLUE_3_WANNA_GO_HOME),
        "position(blue,above)",
        "speak_active",

        "squeak(blue)",
        "text(blue,0,0,2)",
        IDC("Where are we? How did", STRC_INT1BLUE_3_WHERE_ARE_WE),
        NUL("we even get here?"),
        "position(blue,above)",
        "speak_active",

        "squeak(player)",
        "text(player,0,0,4)",
        IDC("Well, Violet did say that the", STRC_INT1BLUE_3_INTERFERENCE_TELE),
        NUL("interference in the dimension"),
        NUL("we crashed in was causing"),
        NUL("problems with the teleporters..."),
        "position(player,below)",
        "speak_active",

        "squeak(player)",
        "text(player,0,0,1)",
        IDC("I guess something went wrong...", STRC_INT1BLUE_3_SOMETHING_WRONG),
        "position(player,below)",
        "speak_active",

        "squeak(player)",
        "text(player,0,0,3)",
        IDC("But if we can find another", STRC_INT1BLUE_3_FIND_ANOTHER_TELE),
        NUL("teleporter, I think we can"),
        NUL("get back to the ship!"),
        "position(player,below)",
        "speak_active",

        "squeak(blue)",
        "text(blue,0,0,1)",
        IDC("Sniff...", STRC_INT1BLUE_3_SNIFF),
        "position(blue,above)",
        "speak_active",
        "endtext",

        "endcutscene()",
        "untilbars()",
        };
        filllines(lines);
    }
    else if (SDL_strcmp(t, "int1blue_4") == 0)
    {
        static const char* lines[] = {
        "cutscene()",
        "untilbars()",
        "face(player,blue)",
        "face(blue,player)",

        "squeak(cry)",
        "text(blue,0,0,1)",
        IDC("Captain! Captain! Wait for me!", STRC_INT1BLUE_4_CAPTAIN_WAIT),
        "position(blue,above)",
        "speak_active",

        "squeak(blue)",
        "text(blue,0,0,2)",
        IDC("Please don't leave me behind!", STRC_INT1BLUE_4_DONT_LEAVE_ME),
        NUL("I don't mean to be a burden!"),
        "position(blue,above)",
        "speak_active",

        "squeak(cry)",
        "text(blue,0,0,1)",
        IDC("I'm scared!", STRC_INT1BLUE_4_IM_SCARED),
        "position(blue,above)",
        "speak_active",

        "squeak(player)",
        "text(player,0,0,2)",
        IDC("Oh... don't worry Victoria,", STRC_INT1BLUE_4_DONT_WORRY),
        NUL("I'll look after you!"),
        "position(player,above)",
        "speak_active",

        "endtext",

        "endcutscene()",
        "untilbars()",
        };
        filllines(lines);
    }
    else if (SDL_strcmp(t, "int1blue_5") == 0)
    {
        static const char* lines[] = {
        "cutscene()",
        "untilbars()",
        "face(player,blue)",
        "face(blue,player)",

        "squeak(cry)",
        "text(blue,0,0,2)",
        IDC("We're never going to get", STRC_INT1BLUE_5_NEVER_GETTING_OUT),
        NUL("out of here, are we?"),
        "position(blue,above)",
        "speak_active",

        "squeak(cry)",
        "changemood(player,1)",
        "text(player,0,0,1)",
        IDC("I.. I don't know...", STRC_INT1BLUE_5_DONT_KNOW),
        "position(player,above)",
        "speak_active",

        "squeak(cry)",
        "text(player,0,0,2)",
        IDC("I don't know where we are or", STRC_INT1BLUE_5_DONT_KNOW_WHERE_OR_HOW),
        NUL("how we're going to get out..."),
        "position(player,above)",
        "speak_active",


        "endtext",

        "endcutscene()",
        "untilbars()",
        };
        filllines(lines);
    }
    else if (SDL_strcmp(t, "int1blue_6") == 0)
    {
        static const char* lines[] = {
        "cutscene()",
        "untilbars()",
        "face(player,blue)",
        "face(blue,player)",

        "squeak(cry)",
        "text(blue,0,0,1)",
        IDC("We're going to be lost forever!", STRC_INT1BLUE_6_LOST_FOREVER),
        "position(blue,above)",
        "speak_active",

        "squeak(player)",
        "changemood(player,0)",
        "text(player,0,0,2)",
        IDC("Ok, come on... Things", STRC_INT1BLUE_6_NOT_THAT_BAD),
        NUL("aren't that bad."),
        "position(player,above)",
        "speak_active",


        "squeak(player)",
        "text(player,0,0,2)",
        IDC("I have a feeling that", STRC_INT1BLUE_6_NEARLY_HOME),
        NUL("we're nearly home!"),
        "position(player,above)",
        "speak_active",

        "squeak(player)",
        "text(player,0,0,2)",
        IDC("We can't be too far", STRC_INT1BLUE_6_ANOTHER_TELE),
        NUL("from another teleporter!"),
        "position(player,above)",
        "speak_active",

        "squeak(cry)",
        "text(blue,0,0,1)",
        IDC("I hope you're right, captain...", STRC_INT1BLUE_6_HOPE_YOURE_RIGHT),
        "position(blue,above)",
        "speak_active",

        "endtext",

        "endcutscene()",
        "untilbars()",
        };
        filllines(lines);
    }
    else if (SDL_strcmp(t, "int1blue_7") == 0)
    {
        static const char* lines[] = {
        "cutscene()",
        "untilbars()",
        "face(player,blue)",
        "face(blue,player)",

        "squeak(blue)",
        "text(blue,0,0,2",
        IDC("Captain! You were right!", STRC_INT1BLUE_7_YOU_WERE_RIGHT),
        NUL("It's a teleporter!"),
        "position(blue,above)",
        "speak_active",

        "squeak(player)",
        "changemood(player,0)",
        "text(player,0,0,3)",
        IDC("Phew! You had me worried for a", STRC_INT1BLUE_7_PHEW),
        NUL("while there... I thought we"),
        NUL("were never going to find one."),
        "position(player,above)",
        "speak_active",


        "squeak(cry)",
        "changemood(blue,1)",
        "text(blue,0,0,1",
        IDC("What? Really?", STRC_INT1BLUE_7_REALLY),
        "position(blue,above)",
        "speak_active",

        "squeak(player)",
        "text(player,0,0,2)",
        IDC("Anyway, let's go", STRC_INT1BLUE_7_BACK_TO_SHIP),
        NUL("back to the ship."),
        "position(player,above)",
        "speak_active",

        "changemood(blue,0)",
        "endtext",

        "endcutscene()",
        "untilbars()",
        };
        filllines(lines);
    }
    else if (SDL_strcmp(t, "int1green_1") == 0)
    {
        static const char* lines[] = {
        "delay(45)",

        "squeak(green)",
        "text(green,0,0,1)",
        IDC("Huh? This isn't the ship...", STRC_INT1GREEN_1_HUH_NOT_SHIP),
        "position(green,above)",
        "speak_active",
        "face(player,green)",
        "face(green,player)",

        "squeak(green)",
        "text(green,0,0,1)",
        IDC("Captain! What's going on?", STRC_INT1GREEN_1_CAPTAIN_WHATS_GOING_ON),
        "position(green,above)",
        "speak_active",

        "squeak(cry)",
        "changemood(player,1",
        "text(player,0,0,1)",
        IDC("I... I don't know!", STRC_INT1GREEN_1_DONT_KNOW),
        "position(player,above)",
        "speak_active",

        "squeak(player)",
        "text(player,0,0,1)",
        IDC("Where are we?", STRC_INT1GREEN_1_WHERE_ARE_WE),
        "position(player,above)",
        "speak_active",

        "squeak(green)",
        "text(green,0,0,3)",
        IDC("Uh oh, this isn't good...", STRC_INT1GREEN_1_GONE_WRONG_TELE),
        NUL("Something must have gone"),
        NUL("wrong with the teleporter!"),
        "position(green,above)",
        "speak_active",

        "squeak(player)",
        "changemood(player,0",
        "text(player,0,0,1)",
        IDC("Ok... no need to panic!", STRC_INT1GREEN_1_NO_NEED_PANIC),
        "position(player,above)",
        "speak_active",

        "squeak(player)",
        "changemood(player,0",
        "text(player,0,0,1)",
        IDC("Let's look for another teleporter!", STRC_INT1GREEN_1_LOOK_FOR_ANOTHER),
        "There's bound to be one around",
        "here somewhere!",
        "position(player,above)",
        "speak_active",

        "endtext",

        "telesave()",
        "endcutscene()",
        "untilbars()",
        "gamestate(14)",
        };
        filllines(lines);
    }
    else if (SDL_strcmp(t, "int1green_2") == 0)
    {
        static const char* lines[] = {
        "cutscene()",
        "untilbars()",

        "squeak(player)",
        "text(player,0,0,1)",
        IDC("Let's go this way!", STRC_INT1GREEN_2_THIS_WAY),
        "position(player,above)",
        "speak_active",

        "squeak(green)",
        "text(green,0,0,1)",
        IDC("After you, Captain!", STRC_INT1GREEN_2_AFTER_YOU),
        "position(green,above)",
        "speak_active",

        "endtext",

        "endcutscene()",
        "untilbars()",
        "gamestate(11)",
        };
        filllines(lines);

    }
    else if (SDL_strcmp(t, "int1green_3") == 0)
    {
        static const char* lines[] = {
        "cutscene()",
        "untilbars()",
        "face(player,green)",
        "face(green,player)",

        "squeak(green)",
        "text(green,0,0,2)",
        IDC("So Violet's back on the", STRC_INT1GREEN_3_SO_VIOLETS_OK),
        NUL("ship? She's really ok?"),
        "position(green,above)",
        "speak_active",

        "squeak(player)",
        "text(player,0,0,2)",
        IDC("She's fine! She helped", STRC_INT1GREEN_3_SHES_FINE),
        NUL("me find my way back!"),
        "position(player,below)",
        "speak_active",

        "squeak(green)",
        "text(green,0,0,1)",
        IDC("Oh, phew! I was worried about her.", STRC_INT1GREEN_3_PHEW_WAS_WORRIED),
        "position(green,above)",
        "speak_active",
        "endtext",

        "delay(45)",

        "squeak(green)",
        "text(green,0,0,1)",
        IDC("Captain, I have a secret...", STRC_INT1GREEN_3_I_HAVE_SECRET),
        "position(green,above)",
        "speak_active",

        "squeak(cry)",
        "changemood(green,1)",
        "text(green,0,0,1)",
        IDC("I really like Violet!", STRC_INT1GREEN_3_LIKE_VIOLET),
        "position(green,above)",
        "speak_active",

        "squeak(player)",
        "text(player,0,0,1)",
        IDC("Is that so?", STRC_INT1GREEN_3_THAT_SO),
        "position(player,below)",
        "speak_active",

        "squeak(green)",
        "changemood(green,0)",
        "text(green,0,0,2)",
        IDC("Please promise you", STRC_INT1GREEN_3_PROMISE_WONT_TELL),
        "won't tell her!",
        "position(green,above)",
        "speak_active",
        "endtext",

        "endcutscene()",
        "untilbars()",
        };
        filllines(lines);
    }
    else if (SDL_strcmp(t, "int1green_4") == 0)
    {
        static const char* lines[] = {
        "cutscene()",
        "untilbars()",
        "face(player,green)",
        "face(green,player)",

        "squeak(green)",
        "text(green,0,0,1)",
        IDC("Hey again!", STRC_INT1GREEN_4_HEY_AGAIN),
        "position(green,above)",
        "speak_active",

        "squeak(player)",
        "text(player,0,0,1)",
        IDC("Hey!", STRC_INT1GREEN_4_HEY),
        "position(player,above)",
        "speak_active",

        "squeak(player)",
        "text(player,0,0,1)",
        IDC("Are you doing ok?", STRC_INT1GREEN_4_YOU_OK),
        "position(player,above)",
        "speak_active",

        "squeak(green)",
        "text(green,0,0,3)",
        IDC("I think so! I really", STRC_INT1GREEN_4_THINK_SO),
        NUL("hope we can find a way"),
        NUL("back to the ship..."),
        "position(green,above)",
        "speak_active",

        "endtext",

        "endcutscene()",
        "untilbars()",
        };
        filllines(lines);
    }
    else if (SDL_strcmp(t, "int1green_5") == 0)
    {
        static const char* lines[] = {
        "cutscene()",
        "untilbars()",
        "face(player,green)",
        "face(green,player)",

        "squeak(green)",
        "text(green,0,0,1)",
        IDC("So, about Violet...", STRC_INT1GREEN_5_ABOUT_VIOLET),
        "position(green,above)",
        "speak_active",

        "squeak(player)",
        "text(player,0,0,1)",
        IDC("Um, yeah?", STRC_INT1GREEN_5_UM_YEAH),
        "position(player,above)",
        "speak_active",

        "squeak(green)",
        "text(green,0,0,1)",
        IDC("Do you have any advice?", STRC_INT1GREEN_5_ANY_ADVICE),
        "position(green,above)",
        "speak_active",

        "squeak(player)",
        "text(player,0,0,1)",
        IDC("Oh!", STRC_INT1GREEN_5_OH_EX),
        "position(player,above)",
        "speak_active",
        "endtext",

        "delay(45)",

        "squeak(player)",
        "text(player,0,0,1)",
        IDC("Hmm...", STRC_INT1GREEN_5_HMM),
        "position(player,above)",
        "speak_active",

        "squeak(player)",
        "text(player,0,0,1)",
        IDC("Um... you should... be yourself!", STRC_INT1GREEN_5_BE_YOURSELF),
        "position(player,above)",
        "speak_active",
        "endtext",

        "delay(15)",

        "squeak(green)",
        "text(green,0,0,1)",
        IDC("Oh.", STRC_INT1GREEN_5_OH),
        "position(green,above)",
        "speak_active",
        "endtext",

        "delay(75)",

        "squeak(green)",
        "text(green,0,0,1)",
        IDC("Thanks Captain!", STRC_INT1GREEN_5_THANKS_CAPTAIN),
        "position(green,above)",
        "speak_active",
        "endtext",

        "endcutscene()",
        "untilbars()",
        };
        filllines(lines);
    }
    else if (SDL_strcmp(t, "int1green_6") == 0)
    {
        static const char* lines[] = {
        "cutscene()",
        "untilbars()",
        "face(player,green)",
        "face(green,player)",

        "squeak(player)",
        "text(player,0,0,2)",
        IDC("So, do you think you'll", STRC_INT1GREEN_6_ABLE_FIX_SHIP),
        NUL("be able to fix the ship?"),
        "position(player,above)",
        "speak_active",

        "squeak(green)",
        "text(green,0,0,2)",
        IDC("Depends on how bad it ", STRC_INT1GREEN_6_DEPENDS_HOW_BAD),
        NUL("is... I think so, though!"),
        "position(green,above)",
        "speak_active",

        "squeak(green)",
        "text(green,0,0,5)",
        IDC("It's not very hard, really. The", STRC_INT1GREEN_6_NOT_VERY_HARD),
        NUL("basic dimensional warping engine"),
        NUL("design is pretty simple, and if we"),
        NUL("can get that working we shouldn't"),
        NUL("have any trouble getting home."),
        "position(green,above)",
        "speak_active",

        "squeak(player)",
        "text(player,0,0,1)",
        IDC("Oh! Good!", STRC_INT1GREEN_6_OH_GOOD),
        "position(player,above)",
        "speak_active",

        "endtext",

        "endcutscene()",
        "untilbars()",
        };
        filllines(lines);
    }
    else if (SDL_strcmp(t, "int1green_7") == 0)
    {
        static const char* lines[] = {
        "cutscene()",
        "untilbars()",
        "face(player,green)",
        "face(green,player)",

        "squeak(green)",
        "text(green,0,0,1)",
        IDC("Finally! A teleporter!", STRC_INT1GREEN_7_FINALLY_TELE),
        "position(green,above)",
        "speak_active",

        "squeak(green)",
        "text(green,0,0,2)",
        IDC("I was getting worried", STRC_INT1GREEN_7_WAS_WORRIED),
        NUL("we wouldn't find one..."),
        "position(green,above)",
        "speak_active",

        "squeak(player)",
        "text(player,0,0,1)",
        IDC("Let's head back to the ship!", STRC_INT1GREEN_7_BACK_TO_SHIP),
        "position(player,above)",
        "speak_active",

        "endtext",

        "endcutscene()",
        "untilbars()",
        };
        filllines(lines);
    }
    else if (SDL_strcmp(t, "int1red_1") == 0)
    {
        static const char* lines[] = {
        "cutscene()",
        "untilbars()",

        "squeak(red)",
        "text(red,0,0,1)",
        IDC("Wow! Where are we?", STRC_INT1RED_1_WHERE_ARE_WE),
        "position(red,above)",
        "speak_active",

        "squeak(cry)",
        "changemood(player,1)",
        "text(player,0,0,3)",
        IDC("This... isn't right...", STRC_INT1RED_1_ISNT_RIGHT_TELE),
        NUL("Something must have gone"),
        NUL("wrong with the teleporter!"),
        "position(player,above)",
        "speak_active",

        "squeak(red)",
        "text(red,0,0,3)",
        IDC("Oh well... We can work", STRC_INT1RED_1_OH_WELL),
        NUL("it out when we get"),
        NUL("back to the ship!"),
        "position(red,above)",
        "speak_active",

        "squeak(red)",
        "text(red,0,0,1)",
        IDC("Let's go exploring!", STRC_INT1RED_1_GO_EXPLORING),
        "position(red,above)",
        "speak_active",

        "squeak(player)",
        "changemood(player,0)",
        "text(player,0,0,1)",
        IDC("Ok then!", STRC_INT1RED_1_OK_THEN),
        "position(player,above)",
        "speak_active",

        "endtext",

        "telesave()",
        "endcutscene()",
        "untilbars()",
        "gamestate(14)",
        };
        filllines(lines);
    }
    else if (SDL_strcmp(t, "int1red_2") == 0)
    {
        static const char* lines[] = {
        "cutscene()",
        "untilbars()",
        "face(player,red)",
        "face(red,player)",

        "squeak(player)",
        "text(player,0,0,1)",
        IDC("Follow me!", STRC_INT1RED_2_FOLLOW_ME),
        "position(player,above)",
        "speak_active",

        "squeak(red)",
        "text(red,0,0,1)",
        IDC("Aye aye, Captain!", STRC_INT1RED_2_AYE_AYE_CAPTAIN),
        "position(red,above)",
        "speak_active",
        "endtext",

        "endcutscene()",
        "untilbars()",
        "gamestate(11)",
        };
        filllines(lines);
    }
    else if (SDL_strcmp(t, "int1red_3") == 0)
    {
        static const char* lines[] = {
        "cutscene()",
        "untilbars()",
        "face(player,red)",
        "face(red,player)",

        "squeak(red)",
        "text(red,0,0,2)",
        IDC("Hey Viridian... how did", STRC_INT1RED_3_VIRIDIAN_HOW_CRASH),
        NUL("the crash happen, exactly?"),
        "position(red,above)",
        "speak_active",

        "squeak(player)",
        "text(player,0,0,2)",
        IDC("Oh, I don't really know -", STRC_INT1RED_3_DONT_KNOW),
        NUL("some sort of interference..."),
        "position(player,below)",
        "speak_active",

        "squeak(player)",
        "text(player,0,0,2)",
        IDC("...or something sciencey like", STRC_INT1RED_3_SOMETHING_SCIENCY),
        NUL("that. It's not really my area."),
        "position(player,below)",
        "speak_active",

        "squeak(red)",
        "text(red,0,0,3)",
        IDC("Ah! Well, do you think", STRC_INT1RED_3_ABLE_FIX_SHIP),
        NUL("we'll be able to fix"),
        NUL("the ship and go home?"),
        "position(red,above)",
        "speak_active",

        "squeak(player)",
        "text(player,0,0,1)",
        IDC("Of course! Everything will be ok!", STRC_INT1RED_3_OF_COURSE),
        "position(player,below)",
        "speak_active",

        "endtext",

        "endcutscene()",
        "untilbars()",
        };
        filllines(lines);
    }
    else if (SDL_strcmp(t, "int1red_4") == 0)
    {
        static const char* lines[] = {
        "cutscene()",
        "untilbars()",
        "face(player,red)",
        "face(red,player)",

        "squeak(red)",
        "text(red,0,0,1)",
        IDC("Hi again! You doing ok?", STRC_INT1RED_4_HI_AGAIN),
        "position(red,above)",
        "speak_active",

        "squeak(player)",
        "text(player,0,0,2)",
        IDC("I think so! But I really want", STRC_INT1RED_4_THINK_SO),
        NUL("to get back to the ship..."),
        "position(player,above)",
        "speak_active",

        "squeak(red)",
        "text(red,0,0,3)",
        IDC("We'll be ok! If we can find", STRC_INT1RED_4_WELL_BE_OK),
        NUL("a teleporter somewhere we"),
        NUL("should be able to get back!"),
        "position(red,above)",
        "speak_active",

        "endtext",

        "endcutscene()",
        "untilbars()",
        };
        filllines(lines);
    }
    else if (SDL_strcmp(t, "int1red_5") == 0)
    {
        static const char* lines[] = {
        "cutscene()",
        "untilbars()",
        "face(player,red)",
        "face(red,player)",

        "squeak(red)",
        "text(red,0,0,1)",
        IDC("Are we there yet?", STRC_INT1RED_5_WE_THERE_YET),
        "position(red,above)",
        "speak_active",

        "squeak(player)",
        "text(player,0,0,1)",
        IDC("We're getting closer, I think...", STRC_INT1RED_5_GETTING_CLOSER),
        "position(player,above)",
        "speak_active",

        "squeak(player)",
        "text(player,0,0,1)",
        IDC("I hope...", STRC_INT1RED_5_I_HOPE),
        "position(player,above)",
        "speak_active",
        "endtext",

        "endcutscene()",
        "untilbars()",
        };
        filllines(lines);
    }
    else if (SDL_strcmp(t, "int1red_6") == 0)
    {
        static const char* lines[] = {
        "cutscene()",
        "untilbars()",
        "face(player,red)",
        "face(red,player)",

        "squeak(player)",
        "text(player,0,0,1)",
        IDC("I wonder where we are, anyway?", STRC_INT1RED_6_WONDER_WHERE),
        "position(player,above)",
        "speak_active",

        "squeak(player)",
        "text(player,0,0,3)",
        IDC("This seems different from", STRC_INT1RED_6_SEEMS_DIFFERENT),
        NUL("that dimension we crashed"),
        NUL("in, somehow..."),
        "position(player,above)",
        "speak_active",

        "squeak(red)",
        "text(red,0,0,2)",
        IDC("I dunno... But we must be", STRC_INT1RED_6_DUNNO),
        NUL("close to a teleporter by now..."),
        "position(red,above)",
        "speak_active",

        "endtext",

        "endcutscene()",
        "untilbars()",
        };
        filllines(lines);
    }
    else if (SDL_strcmp(t, "int1red_7") == 0)
    {
        static const char* lines[] = {
        "cutscene()",
        "untilbars()",
        "face(player,red)",
        "face(red,player)",

        "squeak(player)",
        "text(player,0,0,1)",
        IDC("We're there!", STRC_INT1RED_7_WERE_THERE),
        "position(player,above)",
        "speak_active",

        "squeak(red)",
        "text(red,0,0,2)",
        IDC("See? I told you! Let's", STRC_INT1RED_7_TOLD_YOU),
        NUL("get back to the ship!"),
        "position(red,above)",
        "speak_active",

        "endtext",

        "endcutscene()",
        "untilbars()",
        };
        filllines(lines);
    }
    else if (SDL_strcmp(t, "int1yellow_1") == 0)
    {
        static const char* lines[] = {
        "cutscene()",
        "untilbars()",

        "squeak(yellow)",
        "text(yellow,0,0,1)",
        IDC("Oooh! This is interesting...", STRC_INT1YELLOW_1_INTERESTING),
        "position(yellow,above)",
        "speak_active",

        "squeak(yellow)",
        "text(yellow,0,0,2)",
        IDC("Captain! Have you", STRC_INT1YELLOW_1_CAPTAIN_BEEN_HERE_BEFORE),
        NUL("been here before?"),
        "position(yellow,above)",
        "speak_active",

        "squeak(cry)",
        "changemood(player,1)",
        "text(player,0,0,1)",
        IDC("What? Where are we?", STRC_INT1YELLOW_1_WHAT_WHERE),
        "position(player,above)",
        "speak_active",

        "squeak(yellow)",
        "text(yellow,0,0,3)",
        IDC("I suspect something deflected", STRC_INT1YELLOW_1_DEFLECTED_TELE),
        NUL("our teleporter transmission!"),
        NUL("This is somewhere new..."),
        "position(yellow,above)",
        "speak_active",

        "squeak(cry)",
        "changemood(player,1)",
        "text(player,0,0,1)",
        IDC("Oh no!", STRC_INT1YELLOW_1_OH_NO),
        "position(player,above)",
        "speak_active",

        "squeak(player)",
        "changemood(player,0)",
        "text(player,0,0,3)",
        IDC("We should try to find a", STRC_INT1YELLOW_1_FIND_TELE),
        NUL("teleporter and get back"),
        NUL("to the ship..."),
        "position(player,above)",
        "speak_active",

        "endtext",

        "telesave()",
        "endcutscene()",
        "untilbars()",
        "gamestate(14)",
        };
        filllines(lines);
    }
    else if (SDL_strcmp(t, "int1yellow_2") == 0)
    {
        static const char* lines[] = {
        "cutscene()",
        "untilbars()",
        "face(player,yellow)",
        "face(yellow,player)",

        "squeak(player)",
        "text(player,0,0,1)",
        IDC("Follow me!", STRC_INT1YELLOW_2_FOLLOW_ME),
        "position(player,above)",
        "speak_active",

        "squeak(yellow)",
        "text(yellow,0,0,1)",
        IDC("Right behind you, Captain!", STRC_INT1YELLOW_2_BEHIND_YOU_CAPTAIN),
        "position(yellow,above)",
        "speak_active",
        "endtext",

        "endcutscene()",
        "untilbars()",
        "gamestate(11)",
        };
        filllines(lines);
    }
    else if (SDL_strcmp(t, "int1yellow_3") == 0)
    {
        static const char* lines[] = {
        "cutscene()",
        "untilbars()",
        "face(player,yellow)",
        "face(yellow,player)",

        "squeak(player)",
        "text(player,0,0,2)",
        IDC("What do you make of", STRC_INT1YELLOW_3_WHAT_MAKE_OF_THIS),
        NUL("all this, Professor?"),
        "position(player,below)",
        "speak_active",

        "squeak(yellow)",
        "text(yellow,0,0,4)",
        IDC("I'm guessing this dimension", STRC_INT1YELLOW_3_DIMENSION_INTERFERENCE),
        NUL("has something to do with the"),
        NUL("interference that caused"),
        NUL("us to crash!"),
        "position(yellow,above)",
        "speak_active",

        "squeak(yellow)",
        "text(yellow,0,0,2)",
        IDC("Maybe we'll find the", STRC_INT1YELLOW_3_FIND_CAUSE_HERE),
        NUL("cause of it here?"),
        "position(yellow,above)",
        "speak_active",

        "squeak(player)",
        "text(player,0,0,1)",
        IDC("Oh wow! Really?", STRC_INT1YELLOW_3_WOW_REALLY),
        "position(player,below)",
        "speak_active",

        "squeak(yellow)",
        "text(yellow,0,0,4)",
        IDC("Well, it's just a guess.", STRC_INT1YELLOW_3_JUST_A_GUESS),
        NUL("I'll need to get back to"),
        NUL("the ship before I can do"),
        NUL("any real tests..."),
        "position(yellow,above)",
        "speak_active",

        "endtext",

        "endcutscene()",
        "untilbars()",
        };
        filllines(lines);
    }
    else if (SDL_strcmp(t, "int1yellow_4") == 0)
    {
        static const char* lines[] = {
        "cutscene()",
        "untilbars()",
        "face(player,yellow)",
        "face(yellow,player)",

        "squeak(yellow)",
        "text(yellow,0,0,1)",
        IDC("Ohh! What was that?", STRC_INT1YELLOW_4_WHAT_THAT),
        "position(yellow,above)",
        "speak_active",

        "squeak(player)",
        "text(player,0,0,1)",
        IDC("What was what?", STRC_INT1YELLOW_4_WHAT_WHAT),
        "position(player,above)",
        "speak_active",

        "squeak(yellow)",
        "changeai(yellow,faceleft)", // changedir(yellow,0) doesn't work
        "text(yellow,0,0,2)",
        IDC("That big... C thing!", STRC_INT1YELLOW_4_BIG_C_THING),
        NUL("I wonder what it does?"),
        "position(yellow,above)",
        "speak_active",

        "squeak(cry)",
        "changemood(player,1)",
        "text(player,0,0,2)",
        IDC("Em... I don't really know", STRC_INT1YELLOW_4_DONT_KNOW),
        NUL("how to answer that question..."),
        "position(player,above)",
        "speak_active",

        "squeak(player)",
        "changemood(player,0)",
        "text(player,0,0,3)",
        IDC("It's probably best not", STRC_INT1YELLOW_4_NOT_ACKNOWLEDGE),
        NUL("to acknowledge that"),
        NUL("it's there at all."),
        "position(player,above)",
        "speak_active",

        "squeak(yellow)",
        "changeai(yellow,0)", // Make him face right again
        "text(yellow,0,0,2)",
        IDC("Maybe we should take it back", STRC_INT1YELLOW_4_BACK_TO_SHIP_STUDY),
        NUL("to the ship to study it?"),
        "position(yellow,above)",
        "speak_active",

        "squeak(player)",
        "text(player,0,0,3)",
        IDC("We really shouldn't think", STRC_INT1YELLOW_4_WE_SHOULDNT),
        NUL("about it too much... Let's"),
        NUL("keep moving!"),
        "position(player,above)",
        "speak_active",

        "endtext",

        "endcutscene()",
        "untilbars()",
        };
        filllines(lines);
    }
    else if (SDL_strcmp(t, "int1yellow_5") == 0)
    {
        static const char* lines[] = {
        "cutscene()",
        "untilbars()",
        "face(player,yellow)",
        "face(yellow,player)",

        "squeak(yellow)",
        "text(yellow,0,0,3)",
        IDC("You know, there's", STRC_INT1YELLOW_5_ODD_DIMENSION),
        NUL("something really odd"),
        NUL("about this dimension..."),
        "position(yellow,above)",
        "speak_active",

        "squeak(player)",
        "text(player,0,0,1)",
        IDC("Yeah?", STRC_INT1YELLOW_5_YEAH),
        "position(player,above)",
        "speak_active",

        "squeak(yellow)",
        "changeai(yellow,faceleft)", // changedir(yellow,0) doesn't work
        "text(yellow,0,0,3)",
        IDC("We shouldn't really be able", STRC_INT1YELLOW_5_BETWEEN_DIMENSIONS),
        NUL("to move between dimensions"),
        NUL("with a regular teleporter..."),
        "position(yellow,above)",
        "speak_active",

        "squeak(yellow)",
        "text(yellow,0,0,2)",
        IDC("Maybe this isn't a proper", STRC_INT1YELLOW_5_ISNT_PROPER_DIMENSION),
        NUL("dimension at all?"),
        "position(yellow,above)",
        "speak_active",

        "squeak(yellow)",
        "text(yellow,0,0,4)",
        IDC("Maybe it's some kind of", STRC_INT1YELLOW_5_POLAR_DIMENSION),
        NUL("polar dimension? Something"),
        NUL("artificially created for"),
        NUL("some reason?"),
        "position(yellow,above)",
        "speak_active",

        "squeak(yellow)",
        "changeai(yellow,0)", // Make him face right again
        "text(yellow,0,0,2)",
        IDC("I can't wait to get back to the", STRC_INT1YELLOW_5_CANT_WAIT_SHIP),
        NUL("ship. I have a lot of tests to run!"),
        "position(yellow,above)",
        "speak_active",

        "endtext",

        "endcutscene()",
        "untilbars()",
        };
        filllines(lines);
    }
    else if (SDL_strcmp(t, "int1yellow_6") == 0)
    {
        static const char* lines[] = {
        "cutscene()",
        "untilbars()",
        "face(player,yellow)",
        "face(yellow,player)",

        "squeak(yellow)",
        "text(yellow,0,0,3)",
        IDC("I wonder if there's anything", STRC_INT1YELLOW_6_WORTH_EXPLORING),
        NUL("else in this dimension"),
        NUL("worth exploring?"),
        "position(yellow,above)",
        "speak_active",

        "squeak(player)",
        "text(player,0,0,3)",
        IDC("Maybe... but we should probably", STRC_INT1YELLOW_6_MAYBE),
        NUL("just focus on finding the rest"),
        NUL("of the crew for now..."),
        "position(player,above)",
        "speak_active",
        "endtext",

        "endcutscene()",
        "untilbars()",
        };
        filllines(lines);
    }
    else if (SDL_strcmp(t, "int1yellow_7") == 0)
    {
        static const char* lines[] = {
        "cutscene()",
        "untilbars()",
        "face(player,yellow)",
        "face(yellow,player)",

        "squeak(yellow)",
        "text(yellow,0,0,1)",
        IDC("At last!", STRC_INT1YELLOW_7_AT_LAST),
        "position(yellow,above)",
        "speak_active",

        "squeak(yellow)",
        "text(yellow,0,0,1)",
        IDC("Let's go back to the ship!", STRC_INT1YELLOW_7_BACK_TO_SHIP),
        "position(yellow,above)",
        "speak_active",
        "endtext",

        "endcutscene()",
        "untilbars()",
        };
        filllines(lines);
    }
    else if (SDL_strcmp(t, "skipint2") == 0)
    {
        static const char* lines[] = {
        "finalmode(53,49)",
        "gotoposition(228,129,0)",
        "changedir(player,1)",
        "setcheckpoint()",
        "flash(5)",
        "shake(20)",
        "playef(10)",

        "showplayer()",
        "play(8)",

        "hascontrol()",
        "befadein()",
        };
        filllines(lines);
    }
    else if (SDL_strcmp(t, "intermission_2") == 0)
    {
        static const char* lines[] = {
        "ifskip(skipint2)",
        "finalmode(53,49)",
        "gotoposition(228,129,0)",
        "changedir(player,1)",
        "setcheckpoint()",

        "cutscene()",

        "delay(15)",

        "flash(5)",
        "shake(20)",
        "playef(9)",

        "delay(35)",

        "flash(5)",
        "shake(20)",
        "playef(9)",

        "delay(25)",

        "flash(5)",
        "shake(20)",
        "playef(10)",

        "showplayer()",
        "play(8)",

        "befadein()",

        "changemood(player,1)",
        "text(player,0,0,1)",
        IDC("Uh oh...", STRC_INTERMISSION_2_UH_OH),
        "position(player,above)",
        "speak_active",

        "squeak(player)",
        "changemood(player,1)",
        "text(player,0,0,1)",
        IDC("Not again!", STRC_INTERMISSION_2_NOT_AGAIN),
        "position(player,above)",
        "speak_active",

        "iflast(2,int2intro_yellow)",
        "iflast(3,int2intro_red)",
        "iflast(4,int2intro_green)",
        "iflast(5,int2intro_blue)",
        };
        filllines(lines);
    }
    else if (SDL_strcmp(t, "int2intro_yellow") == 0)
    {
        static const char* lines[] = {
        "squeak(cry)",
        "text(player,0,0,1)",
        IDC("Vitellary? Where are you?", STRC_INT2INTRO_YELLOW_WHERE_ARE_YOU),
        "position(player,above)",
        "speak_active",
        "endtext",
        "delay(15)",

        "flash(5)",
        "shake(20)",
        "playef(10)",
        "delay(15)",

        "changedir(player,0)",

        "createcrewman(150,-20,yellow,1,17,1)",

        "squeak(cry)",
        "text(yellow,170,50,1)",
        IDC("Captain!", STRC_INT2INTRO_YELLOW_CAPTAIN),
        "speak_active",
        "endtext",

        "delay(15)",

        "squeak(player)",
        "changemood(player,0)",
        "text(player,0,0,1)",
        IDC("Hang on! I'll save you!", STRC_INT2INTRO_YELLOW_HANG_ON),
        "position(player,above)",
        "speak_active",

        "endtext",
        "telesave()",

        "endcutscene()",
        "untilbars()",
        };
        filllines(lines);
    }
    else if (SDL_strcmp(t, "int2intro_red") == 0)
    {
        static const char* lines[] = {
        "squeak(cry)",
        "text(player,0,0,1)",
        IDC("Vermilion? Where are you?", STRC_INT2INTRO_RED_WHERE_ARE_YOU),
        "position(player,above)",
        "speak_active",
        "endtext",
        "delay(15)",

        "flash(5)",
        "shake(20)",
        "playef(10)",
        "delay(15)",

        "changedir(player,0)",

        "createcrewman(150,-20,red,0,17,1)",

        "squeak(red)",
        "text(red,170,50,1)",
        IDC("Wheeeee!", STRC_INT2INTRO_RED_WHEEEEE),
        "speak_active",
        "endtext",

        "delay(15)",

        "squeak(player)",
        "changemood(player,0)",
        "text(player,0,0,1)",
        IDC("Hang on! I'll save you!", STRC_INT2INTRO_RED_HANG_ON),
        "position(player,above)",
        "speak_active",

        "endtext",
        "telesave()",

        "endcutscene()",
        "untilbars()",
        };
        filllines(lines);
    }
    else if (SDL_strcmp(t, "int2intro_green") == 0)
    {
        static const char* lines[] = {
        "squeak(cry)",
        "text(player,0,0,1)",
        IDC("Verdigris? Where are you?", STRC_INT2INTRO_GREEN_WHERE_ARE_YOU),
        "position(player,above)",
        "speak_active",
        "endtext",
        "delay(15)",

        "flash(5)",
        "shake(20)",
        "playef(10)",
        "delay(15)",

        "changedir(player,0)",

        "createcrewman(150,-20,green,1,17,1)",

        "squeak(cry)",
        "text(green,170,50,1)",
        IDC("Aaagghh!", STRC_INT2INTRO_GREEN_AAGGHH),
        "speak_active",
        "endtext",

        "delay(15)",

        "squeak(player)",
        "changemood(player,0)",
        "text(player,0,0,1)",
        IDC("Hang on! I'll save you!", STRC_INT2INTRO_GREEN_HANG_ON),
        "position(player,above)",
        "speak_active",

        "endtext",
        "telesave()",

        "endcutscene()",
        "untilbars()",
        };
        filllines(lines);
    }
    else if (SDL_strcmp(t, "int2intro_blue") == 0)
    {
        static const char* lines[] = {
        "squeak(cry)",
        "text(player,0,0,1)",
        IDC("Victoria? Where are you?", STRC_INT2INTRO_BLUE_WHERE_ARE_YOU),
        "position(player,above)",
        "speak_active",
        "endtext",
        "delay(15)",

        "flash(5)",
        "shake(20)",
        "playef(10)",
        "delay(15)",

        "changedir(player,0)",

        "createcrewman(150,-20,blue,1,17,1)",

        "squeak(cry)",
        "text(blue,170,50,1)",
        IDC("Help!", STRC_INT2INTRO_BLUE_HELP),
        "speak_active",
        "endtext",

        "delay(15)",

        "squeak(player)",
        "changemood(player,0)",
        "text(player,0,0,1)",
        IDC("Hang on! I'll save you!", STRC_INT2INTRO_BLUE_HANG_ON),
        "position(player,above)",
        "speak_active",

        "endtext",
        "telesave()",

        "endcutscene()",
        "untilbars()",
        };
        filllines(lines);
    }
    else if (SDL_strcmp(t, "int2_yellow") == 0)
    {
        static const char* lines[] = {
        "ifskip(skipint2yellow)",
        "cutscene()",

        "tofloor()",
        "changeai(yellow,followplayer)",
        "untilbars()",

        "squeak(yellow)",
        "text(yellow,0,0,1)",
        IDC("That was interesting, wasn't it?", STRC_INT2_YELLOW_INTERESTING),
        "position(yellow,above)",
        "speak_active",

        "squeak(cry)",
        "changemood(player,1)",
        "text(player,0,0,1)",
        IDC("I feel dizzy...", STRC_INT2_YELLOW_FEEL_DIZZY),
        "position(player,above)",
        "speak_active",

        "endtext",

        "changemood(player,0)",

        "endcutscene()",
        "untilbars()",
        "companion(10)",
        };
        filllines(lines);
    }
    else if (SDL_strcmp(t, "skipint2yellow") == 0)
    {
        static const char* lines[] = {
        "squeak(yellow)",
        "companion(10)",
        };
        filllines(lines);
    }
    else if (SDL_strcmp(t, "int2_red") == 0)
    {
        static const char* lines[] = {
        "ifskip(skipint2red)",
        "cutscene()",

        "tofloor()",
        "changeai(red,followplayer)",
        "untilbars()",

        "squeak(red)",
        "text(red,0,0,1)",
        IDC("Again! Let's go again!", STRC_INT2_RED_AGAIN_AGAIN),
        "position(red,above)",
        "speak_active",

        "squeak(cry)",
        "changemood(player,1)",
        "text(player,0,0,1)",
        IDC("I feel dizzy...", STRC_INT2_RED_FEEL_DIZZY),
        "position(player,above)",
        "speak_active",

        "endtext",

        "changemood(player,0)",

        "endcutscene()",
        "untilbars()",
        "companion(10)",
        };
        filllines(lines);
    }
    else if (SDL_strcmp(t, "skipint2red") == 0)
    {
        static const char* lines[] = {
        "squeak(red)",
        "companion(10)",
        };
        filllines(lines);
    }
    else if (SDL_strcmp(t, "int2_green") == 0)
    {
        static const char* lines[] = {
        "ifskip(skipint2green)",
        "cutscene()",

        "tofloor()",
        "changeai(green,followplayer)",
        "untilbars()",

        "squeak(green)",
        "text(green,0,0,1)",
        IDC("Phew! You're ok!", STRC_INT2_GREEN_PHEW_YOURE_OK),
        "position(green,above)",
        "speak_active",

        "squeak(cry)",
        "changemood(player,1)",
        "text(player,0,0,1)",
        IDC("I feel dizzy...", STRC_INT2_GREEN_FEEL_DIZZY),
        "position(player,above)",
        "speak_active",

        "endtext",

        "changemood(player,0)",

        "endcutscene()",
        "untilbars()",
        "companion(10)",
        };
        filllines(lines);
    }
    else if (SDL_strcmp(t, "skipint2green") == 0)
    {
        static const char* lines[] = {
        "squeak(green)",
        "companion(10)",
        };
        filllines(lines);
    }
    else if (SDL_strcmp(t, "int2_blue") == 0)
    {
        static const char* lines[] = {
        "ifskip(skipint2blue)",
        "cutscene()",

        "tofloor()",
        "changeai(blue,followplayer)",
        "untilbars()",

        "squeak(cry)",
        "text(blue,0,0,1)",
        IDC("I think I'm going to be sick...", STRC_INT2_BLUE_GONNA_BE_SICK),
        "position(blue,above)",
        "speak_active",

        "squeak(cry)",
        "changemood(player,1)",
        "text(player,0,0,1)",
        IDC("I feel dizzy...", STRC_INT2_BLUE_FEEL_DIZZY),
        "position(player,above)",
        "speak_active",

        "endtext",

        "changemood(player,0)",
        "changemood(blue,0)",

        "endcutscene()",
        "untilbars()",
        "companion(10)",
        };
        filllines(lines);
    }
    else if (SDL_strcmp(t, "skipint2blue") == 0)
    {
        static const char* lines[] = {
        "squeak(blue)",
        "companion(10)",
        };
        filllines(lines);
    }
    else if (SDL_strcmp(t, "startexpolevel_station2") == 0)
    {
        //For the Eurogamer EXPO! Scrap later.
        static const char* lines[] = {
        "fadeout()",
        "musicfadeout()",
        "untilfade()",
        "delay(30)",

        "resetgame",

        "gotoroom(12,14)",
        "gotoposition(126,38,1)",
        "setcheckpoint()",
        "changedir(player,0)",
        "fadein()",

        "stopmusic()",
        "play(1)",
        };
        filllines(lines);
    }
    else if (SDL_strcmp(t, "finallevel_teleporter") == 0)
    {
        static const char* lines[] = {
        "delay(10)",

        "squeak(purple)",
        "text(purple,0,0,1)",
        IDC("Welcome back!", STRC_FINALLEVEL_TELE_WELCOME_BACK),
        "position(purple,above)",
        "speak_active",
        "endtext",

        "delay(30)",

        "squeak(purple)",
        "text(purple,0,0,1)",
        IDC("...", STRC_FINALLEVEL_TELE_DOTDOTDOT),
        "position(purple,above)",
        "speak_active",

        "squeak(purple)",
        "text(purple,0,0,1)",
        IDC("Um, where's Captain Viridian?", STRC_FINALLEVEL_TELE_WHERES_VIRIDIAN),
        "position(purple,above)",
        "speak_active",
        "endtext",

        "delay(30)",

        "walk(left,3)",
        "delay(60)",

        "everybodysad()",
        "squeak(cry)",
        "delay(30)",

        "fadeout()",
        "untilfade()",
        "changemood(player,0)",
        "musicfadeout()",

        "finalmode(46,54)",
        "gotoposition(101,113,0)",
        "setcheckpoint()",
        "changedir(player,1)",
        "restoreplayercolour",
        "fadein()",
        "untilfade()",

        "delay(15)",

        "squeak(player)",
        "text(player,0,0,1)",
        IDC("... Hello?", STRC_FINALLEVEL_TELE_HELLO),
        "position(player,above)",
        "speak_active",

        "squeak(player)",
        "text(player,0,0,1)",
        IDC("Is anyone there?", STRC_FINALLEVEL_TELE_ANYONE_THERE),
        "position(player,above)",
        "speak_active",
        "endtext",

        "missing(player)",

        //"squeak(cry)",
        //"changemood(player,1)",

        "endcutscene()",
        "untilbars()",

        "play(15)",
        "telesave()",
        };
        filllines(lines);
    }
    else if (SDL_strcmp(t, "skipfinal") == 0)
    {
        static const char* lines[] = {
        "finalmode(46,54)",
        "gotoposition(101,113,0)",
        "setcheckpoint()",
        "changedir(player,1)",
        "restoreplayercolour",

        "showplayer()",
        "hascontrol()",
        "missing(player)",
        "play(15)",
        "fadein()",
        "untilfade()",
        };
        filllines(lines);
    }
    else if (SDL_strcmp(t, "startlevel_final") == 0)
    {
        static const char* lines[] = {
        "ifskip(skipfinal)",
        "hideplayer()",
        "cutscene()",
        "untilbars()",
        "activeteleporter()",

        "stopmusic()",
        "play(5)",

        "gotoroom(2,11)",
        "gotoposition(160,120,0)",

        "createcrewman(190,153,purple,0,faceleft)",
        "createrescuedcrew()",

        "fadein()",
        "untilfade()",
        "gamestate(4070)",
        };
        filllines(lines);
    }
    else if (SDL_strcmp(t, "regularreturn") == 0)
    {
        static const char* lines[] = {
        "cutscene()",
        "untilbars()",
        "activeteleporter()",

        "stopmusic()",
        "play(4)",

        "gotoroom(2,11)",
        "gotoposition(160,120,0)",

        "createlastrescued()",

        "fadein()",
        "untilfade()",
        "endcutscene()",
        "setcheckpoint()",
        "gamestate(4010)",
        };
        filllines(lines);
    }
    else if (SDL_strcmp(t, "returntohub") == 0)
    {
        //For the Eurogamer EXPO! Scrap later.
        static const char* lines[] = {
        "fadeout()",
        "musicfadeout()",
        "untilfade()",
        "delay(30)",

        "resetgame",

        "gotoroom(7,8)",
        "gotoposition(145,145,0)",
        "setcheckpoint()",
        "changedir(player,0)",
        "fadein()",

        "stopmusic()",
        "play(4)",
        };
        filllines(lines);
    }
    else if (SDL_strcmp(t, "resetgame") == 0)
    {
        //For the Eurogamer EXPO! Scrap later.
        static const char* lines[] = {
        "resetgame",
        "gotoroom(4,6)",
        "fadein()",
        };
        filllines(lines);
    }
    else if (SDL_strcmp(t, "talkred") == 0)
    {
        static const char* lines[] = {
        "redcontrol",
        };
        filllines(lines);
    }
    else if (SDL_strcmp(t, "talkyellow") == 0)
    {
        static const char* lines[] = {
        "yellowcontrol",
        };
        filllines(lines);
    }
    else if (SDL_strcmp(t, "talkgreen") == 0)
    {
        static const char* lines[] = {
        "greencontrol",
        };
        filllines(lines);
    }
    else if (SDL_strcmp(t, "talkblue") == 0)
    {
        static const char* lines[] = {
        "bluecontrol",
        };
        filllines(lines);
    }
    else if (SDL_strcmp(t, "talkpurple") == 0)
    {
        static const char* lines[] = {
        "purplecontrol",
        };
        filllines(lines);
    }
    else if (SDL_strcmp(t, "talkred_1") == 0)
    {
        static const char* lines[] = {
        "cutscene()",
        "untilbars()",
        "face(player,red)",
        "face(red,player)",

        "squeak(red)",
        "text(red,0,0,1)",
        IDC("Don't worry, Sir!", STRC_TALKRED_1_DONT_WORRY_SIR),
        "position(red,above)",
        "speak_active",

        "squeak(red)",
        "text(red,0,0,2)",
        IDC("We'll find a way", STRC_TALKRED_1_WELL_FIND_WAY_OUT),
        NUL("out of here!"),
        "position(red,above)",
        "speak_active",

        "endtext",

        "endcutscene()",
        "untilbars()",
        "createactivityzone(red)",
        };
        filllines(lines);
    }
    else if (SDL_strcmp(t, "talkred_2") == 0)
    {
        static const char* lines[] = {
        "cutscene()",
        "untilbars()",
        "face(player,red)",
        "face(red,player)",

        "squeak(red)",
        "text(red,0,0,1)",
        IDC("I hope Victoria is ok...", STRC_TALKRED_2_HOPE_VICTORIA_OK),
        "position(red,above)",
        "speak_active",

        "squeak(red)",
        "text(red,0,0,2)",
        IDC("She doesn't handle", STRC_TALKRED_2_DOESNT_HANDLE_SUPRISES),
        NUL("surprises very well..."),
        "position(red,above)",
        "speak_active",

        "endtext",

        "endcutscene()",
        "untilbars()",
        "createactivityzone(red)",
        };
        filllines(lines);
    }
    else if (SDL_strcmp(t, "talkred_3") == 0)
    {
        static const char* lines[] = {
        "cutscene()",
        "untilbars()",
        "face(player,red)",
        "face(red,player)",

        "squeak(red)",
        "text(red,0,0,3)",
        IDC("I don't know how we're", STRC_TALKRED_3_DONT_KNOW_HOW),
        NUL("going to get this ship"),
        NUL("working again!"),
        "position(red,above)",
        "speak_active",

        "squeak(red)",
        "text(red,0,0,2)",
        IDC("Chief Verdigris would", STRC_TALKRED_3_VERDIGRIS_WOULD_KNOW),
        NUL("know what to do..."),
        "position(red,above)",
        "speak_active",

        "endtext",

        "endcutscene()",
        "untilbars()",
        "createactivityzone(red)",
        };
        filllines(lines);
    }
    else if (SDL_strcmp(t, "talkred_4") == 0)
    {
        static const char* lines[] = {
        "cutscene()",
        "untilbars()",
        "face(player,red)",
        "face(red,player)",

        "squeak(red)",
        "text(red,0,0,2)",
        IDC("I wonder what caused", STRC_TALKRED_4_WHAT_CAUSED_CRASH),
        NUL("the ship to crash here?"),
        "position(red,above)",
        "speak_active",

        "squeak(red)",
        "text(red,0,0,3)",
        IDC("It's the shame the Professor", STRC_TALKRED_4_SHAME_NO_PROFESSOR),
        NUL("isn't here, huh? I'm sure he"),
        NUL("could work it out!"),
        "position(red,above)",
        "speak_active",

        "endtext",

        "endcutscene()",
        "untilbars()",
        "createactivityzone(red)",
        };
        filllines(lines);
    }
    else if (SDL_strcmp(t, "talkred_5") == 0)
    {
        static const char* lines[] = {
        "cutscene()",
        "untilbars()",
        "face(player,red)",
        "face(red,player)",

        "squeak(red)",
        "text(red,0,0,1)",
        IDC("It's great to be back!", STRC_TALKRED_5_GREAT_TO_BE_BACK),
        "position(red,above)",
        "speak_active",

        "squeak(red)",
        "text(red,0,0,2)",
        IDC("I can't wait to help you", STRC_TALKRED_5_CANT_WAIT_FIND_CREW),
        NUL("find the rest of the crew!"),
        "position(red,above)",
        "speak_active",

        "squeak(red)",
        "text(red,0,0,2)",
        IDC("It'll be like old", STRC_TALKRED_5_LIKE_OLD_TIMES),
        NUL("times, huh, Captain?"),
        "position(red,above)",
        "speak_active",

        "endtext",

        "endcutscene()",
        "untilbars()",
        "createactivityzone(red)",
        };
        filllines(lines);
    }
    else if (SDL_strcmp(t, "talkred_6") == 0)
    {
        static const char* lines[] = {
        "cutscene()",
        "untilbars()",
        "face(player,red)",
        "face(red,player)",

        "squeak(red)",
        "text(red,0,0,2)",
        IDC("It's good to have", STRC_TALKRED_6_GOOD_TO_HAVE_VICTORIA),
        NUL("Victoria back with us."),
        "position(red,above)",
        "speak_active",

        "squeak(red)",
        "text(red,0,0,2)",
        IDC("She really seems happy to", STRC_TALKRED_6_SHE_SEEMS_HAPPY),
        NUL("get back to work in her lab!"),
        "position(red,above)",
        "speak_active",

        "endtext",

        "endcutscene()",
        "untilbars()",
        "createactivityzone(red)",
        };
        filllines(lines);
    }
    else if (SDL_strcmp(t, "talkred_7") == 0)
    {
        static const char* lines[] = {
        "cutscene()",
        "untilbars()",
        "face(player,red)",
        "face(red,player)",

        "squeak(red)",
        "text(red,0,0,3)",
        IDC("I think I saw Verdigris", STRC_TALKRED_7_SAW_VERDIGRIS),
        NUL("working on the outside"),
        NUL("of the ship!"),
        "position(red,above)",
        "speak_active",

        "endtext",

        "endcutscene()",
        "untilbars()",
        "createactivityzone(red)",
        };
        filllines(lines);
    }
    else if (SDL_strcmp(t, "talkred_8") == 0)
    {
        static const char* lines[] = {
        "cutscene()",
        "untilbars()",
        "face(player,red)",
        "face(red,player)",

        "squeak(red)",
        "text(red,0,0,2)",
        IDC("You found Professor", STRC_TALKRED_8_FOUND_VITELLARY),
        NUL("Vitellary! All right!"),
        "position(red,above)",
        "speak_active",

        "squeak(red)",
        "text(red,0,0,2)",
        IDC("We'll have this interference", STRC_TALKRED_8_INTERFERENCE_THING),
        NUL("thing worked out in no time now!"),
        "position(red,above)",
        "speak_active",

        "endtext",

        "endcutscene()",
        "untilbars()",
        "createactivityzone(red)",
        };
        filllines(lines);
    }
    else if (SDL_strcmp(t, "talkred_9") == 0)
    {
        static const char* lines[] = {
        "cutscene()",
        "untilbars()",
        "face(player,red)",
        "face(red,player)",

        "squeak(red)",
        "text(red,0,0,2)",
        IDC("That other dimension was", STRC_TALKRED_9_OTHER_DIMENSION),
        NUL("really strange, wasn't it?"),
        "position(red,above)",
        "speak_active",

        "squeak(red)",
        "text(red,0,0,2)",
        IDC("I wonder what caused the", STRC_TALKRED_9_WHAT_CAUSED_TELE_THERE),
        NUL("teleporter to send us there?"),
        "position(red,above)",
        "speak_active",

        "endtext",

        "endcutscene()",
        "untilbars()",
        "createactivityzone(red)",
        };
        filllines(lines);
    }
    else if (SDL_strcmp(t, "talkred_10") == 0)
    {
        static const char* lines[] = {
        "cutscene()",
        "untilbars()",
        "face(player,red)",
        "face(red,player)",

        "squeak(red)",
        "text(red,0,0,1)",
        IDC("Heya Captain!", STRC_TALKRED_10_HEYA_CAPTAIN),
        "position(red,above)",
        "speak_active",

        "squeak(red)",
        "text(red,0,0,2)",
        IDC("This way looks a little", STRC_TALKRED_10_LOOKS_DANGEROUS),
        NUL("dangerous..."),
        "position(red,above)",
        "speak_active",

        "endtext",

        "endcutscene()",
        "untilbars()",
        "createactivityzone(red)",
        };
        filllines(lines);
    }
    else if (SDL_strcmp(t, "talkred_11") == 0)
    {
        static const char* lines[] = {
        "cutscene()",
        "untilbars()",
        "face(player,red)",
        "face(red,player)",

        "squeak(red)",
        "text(red,0,0,1)",
        IDC("I'm helping!", STRC_TALKRED_11_IM_HELPING),
        "position(red,above)",
        "speak_active",

        "endtext",

        "endcutscene()",
        "untilbars()",
        "createactivityzone(red)",
        };
        filllines(lines);
    }
    else if (SDL_strcmp(t, "talkred_12") == 0)
    {
        static const char* lines[] = {
        "cutscene()",
        "untilbars()",
        "face(player,red)",
        "face(red,player)",

        "squeak(red)",
        "text(red,0,0,1)",
        IDC("Hey Captain!", STRC_TALKRED_12_HEY_CAPTAIN),
        "position(red,above)",
        "speak_active",

        "squeak(red)",
        "text(red,0,0,3)",
        IDC("I found something interesting", STRC_TALKRED_12_FOUND_WARP_SIGNATURE),
        NUL("around here - the same warp"),
        NUL("signature I saw when I landed!"),
        "position(red,above)",
        "speak_active",

        "squeak(red)",
        "text(red,0,0,2)",
        IDC("Someone from the ship", STRC_TALKRED_12_SOMEONE_NEARBY),
        NUL("must be nearby..."),
        "position(red,above)",
        "speak_active",

        "endtext",

        "endcutscene()",
        "untilbars()",
        "createactivityzone(red)",
        };
        filllines(lines);
    }
    else if (SDL_strcmp(t, "talkred_13") == 0)
    {
        static const char* lines[] = {
        "cutscene()",
        "untilbars()",
        "face(player,red)",
        "face(red,player)",

        "squeak(red)",
        "text(red,0,0,2)",
        IDC("This dimension is pretty", STRC_TALKRED_13_DIMENSION_EXCITING),
        NUL("exciting, isn't it?"),
        "position(red,above)",
        "speak_active",

        "squeak(red)",
        "text(red,0,0,1)",
        IDC("I wonder what we'll find?", STRC_TALKRED_13_WONDER_WHAT_FIND),
        "position(red,above)",
        "speak_active",

        "endtext",

        "endcutscene()",
        "untilbars()",
        "createactivityzone(red)",
        };
        filllines(lines);
    }
    else if (SDL_strcmp(t, "talkred_14") == 0)
    {
        static const char* lines[] = {
        "cutscene()",
        "untilbars()",
        "face(player,red)",
        "face(red,player)",

        "squeak(red)",
        "text(red,0,0,1)",
        IDC("Look what I found!", STRC_TALKRED_14_LOOK_WHAT_I_FOUND),
        "position(red,above)",
        "speak_active",

        "squeak(red)",
        "text(red,0,0,2)",
        IDC("It's pretty hard, I can only", STRC_TALKRED_14_ITS_HARD),
        NUL("last for about 10 seconds..."),
        "position(red,above)",
        "speak_active",

        "endtext",

        "endcutscene()",
        "untilbars()",
        "createactivityzone(red)",
        };
        filllines(lines);
    }
    else if (SDL_strcmp(t, "talkyellow_1") == 0)
    {
        static const char* lines[] = {
        "cutscene()",
        "untilbars()",
        "face(player,yellow)",
        "face(yellow,player)",

        "squeak(yellow)",
        "text(yellow,0,0,2)",
        IDC("I'm making some fascinating", STRC_TALKYELLOW_1_DISCOVERIES),
        NUL("discoveries, captain!"),
        "position(yellow,above)",
        "speak_active",

        "endtext",

        "endcutscene()",
        "untilbars()",
        "createactivityzone(yellow)",
        };
        filllines(lines);
    }
    else if (SDL_strcmp(t, "talkyellow_2") == 0)
    {
        static const char* lines[] = {
        "cutscene()",
        "untilbars()",
        "face(player,yellow)",
        "face(yellow,player)",

        "squeak(yellow)",
        "text(yellow,0,0,3)",
        IDC("This isn't like any", STRC_TALKYELLOW_2_NOT_LIKE_ANY_DIMENSION),
        NUL("other dimension we've"),
        NUL("been to, Captain."),
        "position(yellow,above)",
        "speak_active",

        "squeak(yellow)",
        "text(yellow,0,0,2)",
        IDC("There's something strange", STRC_TALKYELLOW_2_SOMETHING_STRANGE),
        NUL("about this place..."),
        "position(yellow,above)",
        "speak_active",

        "endtext",

        "endcutscene()",
        "untilbars()",
        "createactivityzone(yellow)",
        };
        filllines(lines);
    }
    else if (SDL_strcmp(t, "talkyellow_3") == 0)
    {
        static const char* lines[] = {
        "cutscene()",
        "untilbars()",
        "face(player,yellow)",
        "face(yellow,player)",

        "squeak(yellow)",
        "text(yellow,0,0,3)",
        IDC("Captain, have you noticed", STRC_TALKYELLOW_3_DIMENSION_WRAPS),
        NUL("that this dimension seems"),
        NUL("to wrap around?"),
        "position(yellow,above)",
        "speak_active",

        "squeak(player)",
        "text(player,0,0,1)",
        IDC("Yeah, it's strange...", STRC_TALKYELLOW_3_ITS_STRANGE),
        "position(player,above)",
        "speak_active",

        "squeak(cry)",
        "changemood(yellow,1)",
        "text(yellow,0,0,3)",
        IDC("It looks like this dimension", STRC_TALKYELLOW_3_STABILITY_PROBLEMS),
        NUL("is having the same stability"),
        NUL("problems as our own!"),
        "position(yellow,above)",
        "speak_active",

        "squeak(yellow)",
        "text(yellow,0,0,2)",
        IDC("I hope we're not the", STRC_TALKYELLOW_3_HOPE_NOT_CAUSING),
        NUL("ones causing it..."),
        "position(yellow,above)",
        "speak_active",

        "squeak(cry)",
        "changemood(player,1)",
        "text(player,0,0,1)",
        IDC("What? Do you think we might be?", STRC_TALKYELLOW_3_THINK_WE_MIGHT_BE),
        "position(player,above)",
        "speak_active",

        "squeak(yellow)",
        "changemood(yellow,0)",
        "changemood(player,0)",
        "text(yellow,0,0,2)",
        IDC("No no... that's very", STRC_TALKYELLOW_3_NO_UNLIKELY),
        NUL("unlikely, really..."),
        "position(yellow,above)",
        "speak_active",

        "endtext",

        "endcutscene()",
        "untilbars()",
        "createactivityzone(yellow)",
        };
        filllines(lines);
    }
    else if (SDL_strcmp(t, "talkyellow_4") == 0)
    {
        static const char* lines[] = {
        "cutscene()",
        "untilbars()",
        "face(player,yellow)",
        "face(yellow,player)",

        "squeak(yellow)",
        "text(yellow,0,0,4)",
        IDC("My guess is that whoever used", STRC_TALKYELLOW_4_EXPERIMENTING),
        NUL("to live here was experimenting"),
        NUL("with ways to stop the dimension"),
        NUL("from collapsing."),
        "position(yellow,above)",
        "speak_active",

        "squeak(yellow)",
        "text(yellow,0,0,2)",
        IDC("It would explain why they've", STRC_TALKYELLOW_4_EXPLAIN_WRAPPED),
        NUL("wrapped the edges..."),
        "position(yellow,above)",
        "speak_active",

        "squeak(yellow)",
        "text(yellow,0,0,2)",
        IDC("Hey, maybe that's what's", STRC_TALKYELLOW_4_CAUSING_INTERFERENCE),
        NUL("causing the interference?"),
        "position(yellow,above)",
        "speak_active",

        "endtext",

        "endcutscene()",
        "untilbars()",
        "createactivityzone(yellow)",
        };
        filllines(lines);
    }
    else if (SDL_strcmp(t, "talkyellow_5") == 0)
    {
        static const char* lines[] = {
        "cutscene()",
        "untilbars()",
        "face(player,yellow)",
        "face(yellow,player)",

        "squeak(yellow)",
        "text(yellow,0,0,2)",
        IDC("I wonder where the people who", STRC_TALKYELLOW_5_WHO_LIVED_HERE),
        NUL("used to live here have gone?"),
        "position(yellow,above)",
        "speak_active",

        "endtext",

        "endcutscene()",
        "untilbars()",
        "createactivityzone(yellow)",
        };
        filllines(lines);
    }
    else if (SDL_strcmp(t, "talkyellow_6") == 0)
    {
        static const char* lines[] = {
        "cutscene()",
        "untilbars()",
        "face(player,yellow)",
        "face(yellow,player)",

        "squeak(yellow)",
        "text(yellow,0,0,3)",
        IDC("I think it's no coincidence", STRC_TALKYELLOW_6_NO_CONINCIDENCE),
        NUL("that the teleporter was drawn"),
        NUL("to that dimension..."),
        "position(yellow,above)",
        "speak_active",

        "squeak(yellow)",
        "text(yellow,0,0,4)",
        IDC("There's something there. I", STRC_TALKYELLOW_6_SOMETHING_THERE),
        NUL("think it might be causing the"),
        NUL("interference that's stopping"),
        NUL("us from leaving..."),
        "position(yellow,above)",
        "speak_active",

        "endtext",

        "endcutscene()",
        "untilbars()",
        "createactivityzone(yellow)",
        };
        filllines(lines);
    }
    else if (SDL_strcmp(t, "talkyellow_7") == 0)
    {
        //Vertigris is back
        static const char* lines[] = {
        "cutscene()",
        "untilbars()",
        "face(player,yellow)",
        "face(yellow,player)",

        "squeak(yellow)",
        "text(yellow,0,0,1)",
        IDC("I'm glad Verdigris is alright.", STRC_TALKYELLOW_7_GLAD_VERDIGRIS_ALRIGHT),
        "position(yellow,above)",
        "speak_active",

        "squeak(yellow)",
        "text(yellow,0,0,3)",
        IDC("It'll be a lot easier to find", STRC_TALKYELLOW_7_EASIER_FIND_WAY_OUT),
        NUL("some way out of here now that"),
        NUL("we can get the ship working again!"),
        "position(yellow,above)",
        "speak_active",

        "endtext",

        "endcutscene()",
        "untilbars()",
        "createactivityzone(yellow)",
        };
        filllines(lines);
    }
    else if (SDL_strcmp(t, "talkyellow_8") == 0)
    {
        //Victoria is back
        static const char* lines[] = {
        "cutscene()",
        "untilbars()",
        "face(player,yellow)",
        "face(yellow,player)",

        "squeak(yellow)",
        "text(yellow,0,0,2)",
        IDC("Ah, you've found Doctor", STRC_TALKYELLOW_8_FOUND_VICTORIA),
        NUL("Victoria? Excellent!"),
        "position(yellow,above)",
        "speak_active",

        "squeak(yellow)",
        "text(yellow,0,0,1)",
        IDC("I have lots of questions for her!", STRC_TALKYELLOW_8_HAVE_QUESTIONS),
        "position(yellow,above)",
        "speak_active",

        "endtext",

        "endcutscene()",
        "untilbars()",
        "createactivityzone(yellow)",
        };
        filllines(lines);
    }
    else if (SDL_strcmp(t, "talkyellow_9") == 0)
    {
        //Vermilion is back
        static const char* lines[] = {
        "cutscene()",
        "untilbars()",
        "face(player,yellow)",
        "face(yellow,player)",

        "squeak(yellow)",
        "text(yellow,0,0,3)",
        IDC("Vermilion says that he", STRC_TALKYELLOW_9_TRAPPED_TUNNEL),
        NUL("was trapped in some"),
        NUL("sort of tunnel?"),
        "position(yellow,above)",
        "speak_active",

        "squeak(player)",
        "text(player,0,0,2)",
        IDC("Yeah, it just seemed to", STRC_TALKYELLOW_9_GOING_GOING),
        NUL("keep going and going..."),
        "position(player,above)",
        "speak_active",

        "squeak(yellow)",
        "text(yellow,0,0,2)",
        IDC("Interesting... I wonder", STRC_TALKYELLOW_9_INTERESTING),
        NUL("why it was built?"),
        "position(yellow,above)",
        "speak_active",

        "endtext",

        "endcutscene()",
        "untilbars()",
        "createactivityzone(yellow)",
        };
        filllines(lines);
    }
    else if (SDL_strcmp(t, "talkyellow_10") == 0)
    {
        //Back on the ship!
        static const char* lines[] = {
        "cutscene()",
        "untilbars()",
        "face(player,yellow)",
        "face(yellow,player)",

        "squeak(yellow)",
        "text(yellow,0,0,1)",
        IDC("It's good to be back!", STRC_TALKYELLOW_10_GOOD_TO_BE_BACK),
        "position(yellow,above)",
        "speak_active",

        "squeak(yellow)",
        "text(yellow,0,0,2)",
        IDC("I've got so much work", STRC_TALKYELLOW_10_WORK_CATCH_UP),
        NUL("to catch up on..."),
        "position(yellow,above)",
        "speak_active",

        "endtext",

        "endcutscene()",
        "untilbars()",
        "createactivityzone(yellow)",
        };
        filllines(lines);
    }
    else if (SDL_strcmp(t, "talkyellow_11") == 0)
    {
        //Game Complete
        static const char* lines[] = {
        "cutscene()",
        "untilbars()",
        "face(player,yellow)",
        "face(yellow,player)",

        "squeak(yellow)",
        "text(yellow,0,0,3)",
        IDC("I know it's probably a little", STRC_TALKYELLOW_11_DANGEROUS_STAY),
        NUL("dangerous to stay here now that"),
        NUL("this dimension is collapsing..."),
        "position(yellow,above)",
        "speak_active",

        "squeak(yellow)",
        "text(yellow,0,0,2)",
        IDC("...but it's so rare to find", STRC_TALKYELLOW_11_RARE_INTERESTING),
        NUL("somewhere this interesting!"),
        "position(yellow,above)",
        "speak_active",

        "squeak(yellow)",
        "text(yellow,0,0,2)",
        IDC("Maybe we'll find the answers", STRC_TALKYELLOW_11_FIND_ANSWERS),
        NUL("to our own problems here?"),
        "position(yellow,above)",
        "speak_active",

        "endtext",

        "endcutscene()",
        "untilbars()",
        "createactivityzone(yellow)",
        };
        filllines(lines);
    }
    else if (SDL_strcmp(t, "talkyellow_12") == 0)
    {
        static const char* lines[] = {
        "cutscene()",
        "untilbars()",
        "face(player,yellow)",
        "face(yellow,player)",

        "squeak(yellow)",
        "text(yellow,0,0,1)",
        IDC("Captain! Have you seen this?", STRC_TALKYELLOW_12_CAPTAIN_SEEN_THIS),
        "position(yellow,above)",
        "speak_active",

        "squeak(yellow)",
        "text(yellow,0,0,3)",
        IDC("With their research and ours,", STRC_TALKYELLOW_12_STABILISE_OUR_DIMENSION),
        NUL("we should be able to stabilise"),
        NUL("our own dimension!"),
        "position(yellow,above)",
        "speak_active",

        "squeak(yellow)",
        "text(yellow,0,0,1)",
        IDC("We're saved!", STRC_TALKYELLOW_12_WERE_SAVED),
        "position(yellow,above)",
        "speak_active",

        "endtext",

        "endcutscene()",
        "untilbars()",
        "createactivityzone(yellow)",
        };
        filllines(lines);
    }
    else if (SDL_strcmp(t, "talkgreen_1") == 0)
    {
        static const char* lines[] = {
        "cutscene()",
        "untilbars()",
        "face(player,green)",
        "face(green,player)",

        "squeak(green)",
        "text(green,0,0,1)",
        IDC("I'm an engineer!", STRC_TALKGREEN_1_IM_ENGINEER),
        "position(green,above)",
        "speak_active",

        "endtext",

        "endcutscene()",
        "untilbars()",
        "createactivityzone(green)",
        };
        filllines(lines);
    }
    else if (SDL_strcmp(t, "talkgreen_2") == 0)
    {
        static const char* lines[] = {
        "cutscene()",
        "untilbars()",
        "face(player,green)",
        "face(green,player)",

        "squeak(green)",
        "text(green,0,0,3)",
        IDC("I think I can get this ship", STRC_TALKGREEN_2_CAN_FIX_SHIP),
        NUL("moving again, but it's going"),
        NUL("to take a while..."),
        "position(green,above)",
        "speak_active",

        "endtext",

        "endcutscene()",
        "untilbars()",
        "createactivityzone(green)",
        };
        filllines(lines);
    }
    else if (SDL_strcmp(t, "talkgreen_3") == 0)
    {
        static const char* lines[] = {
        "cutscene()",
        "untilbars()",
        "face(player,green)",
        "face(green,player)",

        "squeak(green)",
        "text(green,0,0,3)",
        IDC("Victoria mentioned something", STRC_TALKGREEN_3_VICTORIA_MENTIONED_LAB),
        NUL("about a lab? I wonder if she"),
        NUL("found anything down there?"),
        "position(green,above)",
        "speak_active",

        "endtext",

        "endcutscene()",
        "untilbars()",
        "createactivityzone(green)",
        };
        filllines(lines);
    }
    else if (SDL_strcmp(t, "talkgreen_4") == 0)
    {
        static const char* lines[] = {
        "cutscene()",
        "untilbars()",
        "face(player,green)",
        "face(green,player)",

        "squeak(green)",
        "text(green,0,0,1)",
        IDC("Vermilion's back! Yey!", STRC_TALKGREEN_4_VERMILIONS_BACK_YEY),
        "position(green,above)",
        "speak_active",

        "endtext",

        "endcutscene()",
        "untilbars()",
        "createactivityzone(green)",
        };
        filllines(lines);
    }
    else if (SDL_strcmp(t, "talkgreen_5") == 0)
    {
        static const char* lines[] = {
        "cutscene()",
        "untilbars()",
        "face(player,green)",
        "face(green,player)",

        "squeak(green)",
        "text(green,0,0,3)",
        IDC("The Professor had lots of", STRC_TALKGREEN_5_PROF_HAD_QUESTIONS),
        NUL("questions about this"),
        NUL("dimension for me..."),
        "position(green,above)",
        "speak_active",

        "squeak(green)",
        "text(green,0,0,2)",
        IDC("We still don't really know", STRC_TALKGREEN_5_DONT_KNOW_MUCH),
        NUL("that much, though."),
        "position(green,above)",
        "speak_active",

        "squeak(green)",
        "text(green,0,0,3)",
        IDC("Until we work out what's", STRC_TALKGREEN_5_WHATS_CAUSING_INTERFERENCE),
        NUL("causing that interference,"),
        NUL("we can't go anywhere."),
        "position(green,above)",
        "speak_active",

        "endtext",

        "endcutscene()",
        "untilbars()",
        "createactivityzone(green)",
        };
        filllines(lines);
    }
    else if (SDL_strcmp(t, "talkgreen_6") == 0)
    {
        static const char* lines[] = {
        "cutscene()",
        "untilbars()",
        "face(player,green)",
        "face(green,player)",

        "squeak(green)",
        "text(green,0,0,2)",
        IDC("I'm so glad that", STRC_TALKGREEN_6_GLAD_VIOLETS_ALRIGHT),
        NUL("Violet's alright!"),
        "position(green,above)",
        "speak_active",

        "endtext",

        "endcutscene()",
        "untilbars()",
        "createactivityzone(green)",
        };
        filllines(lines);
    }
    else if (SDL_strcmp(t, "talkgreen_7") == 0)
    {
        static const char* lines[] = {
        "cutscene()",
        "untilbars()",
        "face(player,green)",
        "face(green,player)",

        "squeak(green)",
        "text(green,0,0,3)",
        IDC("That other dimension we ended", STRC_TALKGREEN_7_RELATED_DIMENSION),
        NUL("up in must be related to this"),
        NUL("one, somehow..."),
        "position(green,above)",
        "speak_active",

        "endtext",

        "endcutscene()",
        "untilbars()",
        "createactivityzone(green)",
        };
        filllines(lines);
    }
    else if (SDL_strcmp(t, "talkgreen_8") == 0)
    {
        static const char* lines[] = {
        "cutscene()",
        "untilbars()",
        "face(player,green)",
        "face(green,player)",

        "squeak(cry)",
        "text(green,0,0,3)",
        IDC("The antenna's broken!", STRC_TALKGREEN_8_ANTENNAS_BROKEN),
        NUL("This is going to be"),
        NUL("very hard to fix..."),
        "position(green,above)",
        "speak_active",

        "endtext",

        "endcutscene()",
        "untilbars()",
        "createactivityzone(green)",
        };
        filllines(lines);
    }
    else if (SDL_strcmp(t, "talkgreen_9") == 0)
    {
        static const char* lines[] = {
        "cutscene()",
        "untilbars()",
        "face(player,green)",
        "face(green,player)",

        "squeak(green)",
        "text(green,0,0,2)",
        IDC("It looks like we were warped", STRC_TALKGREEN_9_WARPED_INTO_ROCK),
        NUL("into solid rock when we crashed!"),
        "position(green,above)",
        "speak_active",

        "squeak(green)",
        "text(green,0,0,2)",
        IDC("Hmm. It's going to be hard", STRC_TALKGREEN_9_HARD_TO_SEPARATE),
        NUL("to separate from this..."),
        "position(green,above)",
        "speak_active",

        "endtext",

        "endcutscene()",
        "untilbars()",
        "createactivityzone(green)",
        };
        filllines(lines);
    }
    else if (SDL_strcmp(t, "talkgreen_10") == 0)
    {
        static const char* lines[] = {
        "cutscene()",
        "untilbars()",
        "face(player,green)",
        "face(green,player)",

        "squeak(green)",
        "text(green,0,0,2)",
        IDC("The ship's all fixed up. We", STRC_TALKGREEN_10_SHIPS_FIXED),
        NUL("can leave at a moment's notice!"),
        "position(green,above)",
        "speak_active",

        "endtext",

        "endcutscene()",
        "untilbars()",
        "createactivityzone(green)",
        };
        filllines(lines);
    }
    else if (SDL_strcmp(t, "talkgreen_11") == 0)
    {
        static const char* lines[] = {
        "cutscene()",
        "untilbars()",
        "face(player,green)",
        "face(green,player)",

        "squeak(green)",
        "text(green,0,0,3)",
        IDC("I wonder why they abandoned this", STRC_TALKGREEN_11_WONDER_ABANDONED),
        NUL("dimension? They were so close to"),
        NUL("working out how to fix it..."),
        "position(green,above)",
        "speak_active",

        "squeak(green)",
        "text(green,0,0,2)",
        IDC("Maybe we can fix it for them?", STRC_TALKGREEN_11_FIX_FOR_THEM),
        NUL("Maybe they'll come back?"),
        "position(green,above)",
        "speak_active",
        "endtext",

        "endcutscene()",
        "untilbars()",
        "createactivityzone(green)",
        };
        filllines(lines);

    }


    if (SDL_strcmp(t, "talkpurple_1") == 0)
    {
        static const char* lines[] = {
        "cutscene()",
        "untilbars()",
        "face(player,purple)",
        "face(purple,player)",

        "squeak(cry)",
        "changemood(purple,1)",
        "text(purple,0,0,1)",
        IDC("... I hope Verdigris is alright.", STRC_TALKPURPLE_1_HOPE_VERDIGRIS_ALRIGHT),
        "position(purple,above)",
        "speak_active",

        "squeak(purple)",
        "changemood(purple,0)",
        "text(purple,0,0,2)",
        IDC("If you can find him, he'd be", STRC_TALKPURPLE_1_HED_HELP_FIX),
        NUL("a big help fixing the ship!"),
        "position(purple,above)",
        "speak_active",

        "endtext",

        "endcutscene()",
        "untilbars()",
        "createactivityzone(purple)",
        };
        filllines(lines);
    }
    else if (SDL_strcmp(t, "talkpurple_2") == 0)
    {
        static const char* lines[] = {
        "cutscene()",
        "untilbars()",
        "face(player,purple)",
        "face(purple,player)",

        "squeak(purple)",
        "text(purple,0,0,2)",
        IDC("Chief Verdigris is so brave", STRC_TALKPURPLE_2_VERDIGRIS_BRAVE_SMART),
        NUL("and ever so smart!"),
        "position(purple,above)",
        "speak_active",

        "endtext",

        "endcutscene()",
        "untilbars()",
        "createactivityzone(purple)",
        };
        filllines(lines);
    }
    else if (SDL_strcmp(t, "talkpurple_3") == 0)
    {
        static const char* lines[] = {
        "cutscene()",
        "untilbars()",
        "face(player,purple)",
        "face(purple,player)",

        "squeak(purple)",
        "text(purple,0,0,1)",
        IDC("Are you doing ok, Captain?", STRC_TALKPURPLE_3_YOU_OK_CAPTAIN),
        "position(purple,above)",
        "speak_active",

        "squeak(cry)",
        "changemood(player,1)",
        "text(player,0,0,0)",
        "specialline(1)",
        "position(player,above)",
        "speak_active",

        "squeak(purple)",
        "text(purple,0,0,2)",
        IDC("Oh - well, don't worry,", STRC_TALKPURPLE_3_DONT_WORRY),
        NUL("they'll show up!"),
        "position(purple,above)",
        "speak_active",

        "changemood(player,0)",
        "squeak(purple)",
        "text(purple,0,0,1)",
        IDC("Here! Have a lollipop!", STRC_TALKPURPLE_3_HAVE_LOLLIPOP),
        "position(purple,above)",
        "speak_active",

        "endtext",

        "endcutscene()",
        "untilbars()",
        "createactivityzone(purple)",
        };
        filllines(lines);
    }
    else if (SDL_strcmp(t, "talkpurple_4") == 0)
    {
        static const char* lines[] = {
        "cutscene()",
        "untilbars()",
        "face(player,purple)",
        "face(purple,player)",

        "squeak(purple)",
        "text(purple,0,0,1)",
        IDC("Welcome back, Captain!", STRC_TALKPURPLE_4_WELCOME_BACK),
        "position(purple,above)",
        "speak_active",

        "squeak(purple)",
        "text(purple,0,0,2)",
        IDC("I think Victoria is quite happy", STRC_TALKPURPLE_4_VICTORIA_HAPPY),
        NUL("to be back on the ship."),
        "position(purple,above)",
        "speak_active",

        "squeak(purple)",
        "text(purple,0,0,2)",
        IDC("She really doesn't like adventuring.", STRC_TALKPURPLE_4_SHE_GETS_HOMESICK),
        NUL("She gets very homesick!"),
        "position(purple,above)",
        "speak_active",

        "endtext",

        "endcutscene()",
        "untilbars()",
        "createactivityzone(purple)",
        };
        filllines(lines);
    }
    else if (SDL_strcmp(t, "talkpurple_5") == 0)
    {
        static const char* lines[] = {
        "cutscene()",
        "untilbars()",
        "face(player,purple)",
        "face(purple,player)",

        "squeak(purple)",
        "text(purple,0,0,2)",
        IDC("Vermilion called in", STRC_TALKPURPLE_5_VERMILION_CALLED),
        NUL("to say hello!"),
        "position(purple,above)",
        "speak_active",

        "squeak(purple)",
        "text(purple,0,0,1)",
        NUL("He's really looking forward"),
        "specialline(2)",
        "position(purple,above)",
        "speak_active",

        "endtext",

        "endcutscene()",
        "untilbars()",
        "createactivityzone(purple)",
        };
        filllines(lines);
    }
    else if (SDL_strcmp(t, "talkpurple_6") == 0)
    {
        static const char* lines[] = {
        "cutscene()",
        "untilbars()",
        "face(player,purple)",
        "face(purple,player)",

        "squeak(purple)",
        "text(purple,0,0,1)",
        IDC("Captain! You found Verdigris!", STRC_TALKPURPLE_6_FOUND_VERDIGRIS),
        "position(purple,above)",
        "speak_active",

        "squeak(purple)",
        "text(purple,0,0,1)",
        IDC("Thank you so much!", STRC_TALKPURPLE_6_THANK_YOU_MUCH),
        "position(purple,above)",
        "speak_active",

        "endtext",

        "endcutscene()",
        "untilbars()",
        "createactivityzone(purple)",
        };
        filllines(lines);
    }
    else if (SDL_strcmp(t, "talkpurple_7") == 0)
    {
        static const char* lines[] = {
        "cutscene()",
        "untilbars()",
        "face(player,purple)",
        "face(purple,player)",

        "squeak(purple)",
        "text(purple,0,0,2)",
        IDC("I'm glad Professor", STRC_TALKPURPLE_7_GLAD_VITELLARY_OK),
        NUL("Vitellary is ok!"),
        "position(purple,above)",
        "speak_active",

        "squeak(purple)",
        "text(purple,0,0,2)",
        IDC("He had lots of questions", STRC_TALKPURPLE_7_HE_HAD_QUESTIONS),
        NUL("for me about this dimension."),
        "position(purple,above)",
        "speak_active",

        "squeak(purple)",
        "text(purple,0,0,2)",
        IDC("He's already gotten to", STRC_TALKPURPLE_7_ALREADY_RESEARCH),
        NUL("work with his research!"),
        "position(purple,above)",
        "speak_active",

        "endtext",

        "endcutscene()",
        "untilbars()",
        "createactivityzone(purple)",
        };
        filllines(lines);
    }
    else if (SDL_strcmp(t, "talkpurple_8") == 0)
    {
        static const char* lines[] = {
        "cutscene()",
        "untilbars()",
        "face(player,purple)",
        "face(purple,player)",

        "squeak(purple)",
        "text(purple,0,0,4)",
        IDC("Hey Captain! Now that you've turned", STRC_TALKPURPLE_8_TURNED_OFF_SOURCE),
        NUL("off the source of the interference,"),
        NUL("we can warp everyone back to the"),
        NUL("ship instantly, if we need to!"),
        "position(purple,above)",
        "speak_active",

        "squeak(purple)",
        "text(purple,0,0,3)",
        IDC("Any time you want to come back", STRC_TALKPURPLE_8_SHIP_OPTION),
        NUL("to the ship, just select the"),
        NUL("new SHIP option in your menu!"),
        "position(purple,above)",
        "speak_active",

        "endtext",

        "endcutscene()",
        "untilbars()",
        "createactivityzone(purple)",
        };
        filllines(lines);
    }
    else if (SDL_strcmp(t, "talkpurple_9") == 0)
    {
        static const char* lines[] = {
        "cutscene()",
        "untilbars()",
        "face(player,purple)",
        "face(purple,player)",

        "squeak(purple)",
        "text(purple,0,0,3)",
        IDC("Look at all this research!", STRC_TALKPURPLE_9_LOOK_THIS_RESEARCH),
        NUL("This is going to be a big"),
        NUL("help back home!"),
        "position(purple,above)",
        "speak_active",

        "endtext",

        "endcutscene()",
        "untilbars()",
        "createactivityzone(purple)",
        };
        filllines(lines);
    }
    else if (SDL_strcmp(t, "talkpurple_intermission1") == 0)
    {
        static const char* lines[] = {
        "cutscene()",
        "untilbars()",
        "face(player,purple)",
        "face(purple,player)",

        "squeak(player)",
        "text(player,0,0,3)",
        IDC("Doctor, something strange", STRC_TALKPURPLE_INT1_STRANGE_TELE_TO_SHIP),
        NUL("happened when we teleported"),
        NUL("back to the ship..."),
        "position(player,above)",
        "speak_active",

        "squeak(cry)",
        "changemood(player,1)",
        "text(player,0,0,1)",
        IDC("We got lost in another dimension!", STRC_TALKPURPLE_INT1_GOT_LOST_DIMENSION),
        "position(player,above)",
        "speak_active",

        "squeak(cry)",
        "changemood(purple,1)",
        "text(purple,0,0,1)",
        IDC("Oh no!", STRC_TALKPURPLE_INT1_OH_NO),
        "position(purple,above)",
        "speak_active",

        "squeak(purple)",
        "changemood(purple,0)",
        "changemood(player,0)",
        "text(purple,0,0,3)",
        IDC("Maybe that dimension has something", STRC_TALKPURPLE_INT1_MAYBE_DIMENSION_INTERFERENCE),
        NUL("to do with the interference that"),
        NUL("caused us to crash here?"),
        "position(purple,above)",
        "speak_active",

        "squeak(purple)",
        "text(purple,0,0,1)",
        IDC("I'll look into it...", STRC_TALKPURPLE_INT1_ILL_LOOK_INTO_IT),
        "position(purple,above)",
        "speak_active",

        "endtext",

        "endcutscene()",
        "untilbars()",
        "createactivityzone(purple)",
        };
        filllines(lines);
    }
    else if (SDL_strcmp(t, "talkpurple_intermission2") == 0)
    {
        static const char* lines[] = {
        "cutscene()",
        "untilbars()",
        "face(player,purple)",
        "face(purple,player)",

        "squeak(cry)",
        "changemood(player,1)",
        "text(player,0,0,1)",
        IDC("Doctor! Doctor! It happened again!", STRC_TALKPURPLE_INT2_IT_HAPPENED_AGAIN),
        "position(player,above)",
        "speak_active",

        "squeak(player)",
        "text(player,0,0,2)",
        IDC("The teleporter brought us", STRC_TALKPURPLE_INT2_WEIRD_DIMENSION),
        NUL("to that weird dimension..."),
        "position(player,above)",
        "speak_active",

        "squeak(purple)",
        "changemood(player,0)",
        "changemood(purple,0)",
        "text(purple,0,0,2)",
        IDC("Hmm, there's definitely", STRC_TALKPURPLE_INT2_DEFINITELY_STRANGE),
        NUL("something strange happening..."),
        "position(purple,above)",
        "speak_active",

        "squeak(purple)",
        "text(purple,0,0,2)",
        IDC("If only we could find the", STRC_TALKPURPLE_INT2_FIND_SOURCE),
        NUL("source of that interference!"),
        "position(purple,above)",
        "speak_active",

        "endtext",

        "endcutscene()",
        "untilbars()",
        "createactivityzone(purple)",
        };
        filllines(lines);
    }
    else if (SDL_strcmp(t, "talkpurple_intermission3") == 0)
    {
        static const char* lines[] = {
        "cutscene()",
        "untilbars()",
        "face(player,purple)",
        "face(purple,player)",

        "squeak(player)",
        "text(player,0,0,3)",
        IDC("Doctor, something strange has", STRC_TALKPURPLE_INT3_STRANGE_TELE_TO_SHIP),
        NUL("been happening when we teleport"),
        NUL("back to the ship..."),
        "position(player,above)",
        "speak_active",

        "squeak(cry)",
        "changemood(player,1)",
        "text(player,0,0,2)",
        IDC("We keep getting brought to", STRC_TALKPURPLE_INT3_WEIRD_DIMENSION),
        NUL("another weird dimension!"),
        "position(player,above)",
        "speak_active",

        "squeak(cry)",
        "changemood(purple,1)",
        "text(purple,0,0,1)",
        IDC("Oh no!", STRC_TALKPURPLE_INT3_OH_NO),
        "position(purple,above)",
        "speak_active",

        "squeak(purple)",
        "changemood(purple,0)",
        "changemood(player,0)",
        "text(purple,0,0,3)",
        IDC("Maybe that dimension has something", STRC_TALKPURPLE_INT3_MAYBE_DIMENSION_INTERFERENCE),
        NUL("to do with the interference that"),
        NUL("caused us to crash here?"),
        "position(purple,above)",
        "speak_active",

        "squeak(purple)",
        "changemood(player,0)",
        "changemood(purple,0)",
        "text(purple,0,0,2)",
        IDC("Hmm, there's definitely", STRC_TALKPURPLE_INT3_DEFINITELY_STRANGE),
        NUL("something strange happening..."),
        "position(purple,above)",
        "speak_active",

        "squeak(purple)",
        "text(purple,0,0,2)",
        IDC("If only we could find the", STRC_TALKPURPLE_INT3_FIND_SOURCE),
        NUL("source of that interference!"),
        "position(purple,above)",
        "speak_active",

        "endtext",

        "endcutscene()",
        "untilbars()",
        "createactivityzone(purple)",
        };
        filllines(lines);
    }
    else if (SDL_strcmp(t, "talkpurple_intro") == 0)
    {
        static const char* lines[] = {
        "cutscene()",
        "untilbars()",
        "face(player,purple)",
        "face(purple,player)",

        "squeak(cry)",
        "changemood(player,1)",
        "text(player,0,0,2)",
        IDC("I'm feeling a bit", STRC_TALKPURPLE_INTRO_OVERWHELMED),
        NUL("overwhelmed, Doctor."),
        "position(player,above)",
        "speak_active",

        "squeak(player)",
        "text(player,0,0,1)",
        IDC("Where do I begin?", STRC_TALKPURPLE_INTRO_WHERE_BEGIN),
        "position(player,above)",
        "speak_active",

        "squeak(purple)",
        "text(purple,0,0,2)",
        IDC("Remember that you can press {b_map}", STRC_TALKPURPLE_INTRO_CHECK_MAP),
        NUL("to check where you are on the map!"),
        "position(purple,above)",
        "textbuttons()",
        "speak_active",

        "squeak(purple)",
        "text(purple,0,0,2)",
        IDC("Look for areas where the rest", STRC_TALKPURPLE_INTRO_LOOK_AREAS),
        NUL("of the crew might be..."),
        "position(purple,above)",
        "speak_active",

        "squeak(purple)",
        "text(purple,0,0,2)",
        IDC("If you get lost, you can get back", STRC_TALKPURPLE_INTRO_LOST_TELE_SHIP),
        NUL("to the ship from any teleporter."),
        "position(purple,above)",
        "speak_active",

        "squeak(purple)",
        "text(purple,0,0,2)",
        IDC("And don't worry!", STRC_TALKPURPLE_INTRO_DONT_WORRY),
        NUL("We'll find everyone!"),
        "position(purple,above)",
        "speak_active",

        "endtext",

        "delay(30)",

        "changemood(player,0)",
        "squeak(purple)",
        "text(purple,0,0,1)",
        IDC("Everything will be ok!", STRC_TALKPURPLE_INTRO_WILL_BE_OK),
        "position(purple,above)",
        "speak_active",

        "endtext",

        "endcutscene()",
        "untilbars()",
        "createactivityzone(purple)",
        };
        filllines(lines);
    }
    else if (SDL_strcmp(t, "talkblue_1") == 0)
    {
        static const char* lines[] = {
        "cutscene()",
        "untilbars()",
        "face(player,blue)",
        "face(blue,player)",

        "squeak(blue)",
        "changetile(blue,6)", //smiling again! blue always needs to specify her mood
        "text(blue,0,0,1)",
        IDC("Any signs of Professor Vitellary?", STRC_TALKBLUE_1_SIGNS_OF_VITELLARY),
        "position(blue,below)",
        "speak_active",

        "squeak(player)",
        "text(player,0,0,1)",
        IDC("Sorry, not yet...", STRC_TALKBLUE_1_NOT_YET),
        "position(player,above)",
        "speak_active",

        "squeak(cry)",
        "changetile(blue,150)", //upside down frown :(
        "text(blue,0,0,1)",
        IDC("I hope he's ok...", STRC_TALKBLUE_1_HOPE_HES_OK),
        "position(blue,below)",
        "speak_active",

        "endtext",

        "endcutscene()",
        "untilbars()",
        "createactivityzone(blue)",
        };
        filllines(lines);
    }
    else if (SDL_strcmp(t, "talkblue_2") == 0)
    {
        static const char* lines[] = {
        "cutscene()",
        "untilbars()",
        "face(player,blue)",
        "face(blue,player)",

        "squeak(blue)",
        "changetile(blue,6)", //smiling again! blue always needs to specify her mood
        "text(blue,0,0,2)",
        IDC("Thanks so much for", STRC_TALKBLUE_2_THANKS_FOR_SAVING),
        NUL("saving me, Captain!"),
        "position(blue,below)",
        "speak_active",

        "endtext",

        "endcutscene()",
        "untilbars()",
        "createactivityzone(blue)",
        };
        filllines(lines);
    }
    else if (SDL_strcmp(t, "talkblue_3") == 0)
    {
        static const char* lines[] = {
        "cutscene()",
        "untilbars()",
        "face(player,blue)",
        "face(blue,player)",

        "squeak(blue)",
        "changetile(blue,6)", //smiling again! blue always needs to specify her mood
        "text(blue,0,0,1)",
        IDC("I'm so glad to be back!", STRC_TALKBLUE_3_GLAD_TO_BE_BACK),
        "position(blue,below)",
        "speak_active",

        "squeak(cry)",
        "changetile(blue,150)", //upside down frown :(
        "text(blue,0,0,3)",
        IDC("That lab was so dark", STRC_TALKBLUE_3_LAB_WAS_SCARY),
        "and scary! I didn't",
        "like it at all...",
        "position(blue,below)",
        "speak_active",

        "endtext",

        "endcutscene()",
        "untilbars()",
        "createactivityzone(blue)",
        };
        filllines(lines);
    }
    else if (SDL_strcmp(t, "talkblue_4") == 0)
    {
        static const char* lines[] = {
        "cutscene()",
        "untilbars()",
        "face(player,blue)",
        "face(blue,player)",

        "squeak(blue)",
        "changetile(blue,6)", //smiling again! blue always needs to specify her mood
        "text(blue,0,0,2)",
        IDC("Vitellary's back? I", STRC_TALKBLUE_4_VITELLARYS_BACK),
        NUL("knew you'd find him!"),
        "position(blue,below)",
        "speak_active",

        "squeak(blue)",
        "changetile(blue,6)", //smiling again! blue always needs to specify her mood
        "text(blue,0,0,2)",
        IDC("I mean, I admit I was very", STRC_TALKBLUE_4_ADMIT_WAS_WORRIED),
        NUL("worried that you wouldn't..."),
        "position(blue,below)",
        "speak_active",

        "squeak(cry)",
        "changetile(blue,150)", //upside down frown :(
        "text(blue,0,0,2)",
        IDC("or that something might", STRC_TALKBLUE_4_MIGHTVE_HAPPENED),
        NUL("have happened to him..."),
        "position(blue,below)",
        "speak_active",

        "squeak(blue)",
        "text(blue,0,0,1)",
        IDC("sniff...", STRC_TALKBLUE_4_SNIFF),
        "position(blue,below)",
        "speak_active",

        "endtext",

        "delay(30)",

        "squeak(player)",
        "text(player,0,0,1)",
        IDC("Doctor Victoria? He's ok!", STRC_TALKBLUE_4_HES_OK),
        "position(player,above)",
        "speak_active",

        "squeak(cry)",
        "changetile(blue,150)", //upside down frown :(
        "text(blue,0,0,3)",
        IDC("Oh! Sorry! I was just", STRC_TALKBLUE_4_WHAT_IF_HE_WASNT),
        NUL("thinking about what"),
        NUL("if he wasn't?"),
        "position(blue,below)",
        "speak_active",

        "endtext",

        "delay(30)",

        "squeak(blue)",
        "changetile(blue,6)", //smiling again! blue always needs to specify her mood
        "text(blue,0,0,1)",
        IDC("Thank you, Captain!", STRC_TALKBLUE_4_THANK_YOU),
        "position(blue,below)",
        "speak_active",

        "endtext",

        "endcutscene()",
        "untilbars()",
        "createactivityzone(blue)",
        };
        filllines(lines);
    }
    else if (SDL_strcmp(t, "talkblue_5") == 0)
    {
        static const char* lines[] = {
        "cutscene()",
        "untilbars()",
        "face(player,blue)",
        "face(blue,player)",

        "squeak(blue)",
        "changetile(blue,6)", //smiling again! blue always needs to specify her mood
        "text(blue,0,0,1)",
        IDC("You found Vermilion! Great!", STRC_TALKBLUE_5_FOUND_VERMILION),
        "position(blue,below)",
        "speak_active",

        "squeak(blue)",
        "changetile(blue,6)", //smiling again! blue always needs to specify her mood
        "text(blue,0,0,2)",
        IDC("I wish he wasn't", STRC_TALKBLUE_5_WISH_HE_WASNT_RECKLESS),
        NUL("so reckless!"),
        "position(blue,below)",
        "speak_active",

        "squeak(cry)",
        "changetile(blue,150)", //upside down frown :(
        "text(blue,0,0,2)",
        IDC("He'll get himself", STRC_TALKBLUE_5_GET_HIMSELF_TROUBLE),
        NUL("into trouble..."),
        "position(blue,below)",
        "speak_active",

        "endtext",

        "endcutscene()",
        "untilbars()",
        "createactivityzone(blue)",
        };
        filllines(lines);
    }
    else if (SDL_strcmp(t, "talkblue_6") == 0)
    {
        static const char* lines[] = {
        "cutscene()",
        "untilbars()",
        "face(player,blue)",
        "face(blue,player)",

        "squeak(blue)",
        "changetile(blue,6)", //smiling again! blue always needs to specify her mood
        "text(blue,0,0,2)",
        IDC("Verdigris is ok! Violet", STRC_TALKBLUE_6_VERDIGRIS_OK),
        NUL("will be so happy!"),
        "position(blue,below)",
        "speak_active",

        "squeak(blue)",
        "changetile(blue,6)", //smiling again! blue always needs to specify her mood
        "text(blue,0,0,1)",
        IDC("I'm happy!", STRC_TALKBLUE_6_IM_HAPPY),
        "position(blue,below)",
        "speak_active",

        "endtext",

        "delay(30)",

        "squeak(cry)",
        "changetile(blue,150)", //upside down frown :(
        "text(blue,0,0,1)",
        IDC("Though I was very worried...", STRC_TALKBLUE_6_WAS_WORRIED),
        "position(blue,below)",
        "speak_active",

        "endtext",

        "endcutscene()",
        "untilbars()",
        "createactivityzone(blue)",
        };
        filllines(lines);
    }
    else if (SDL_strcmp(t, "talkblue_7") == 0)
    {
        static const char* lines[] = {
        "cutscene()",
        "untilbars()",
        "face(player,blue)",
        "face(blue,player)",

        "squeak(cry)",
        "changetile(blue,150)", //upside down frown :(
        "text(blue,0,0,2)",
        IDC("Why did the teleporter send", STRC_TALKBLUE_7_WHY_TELE_SCARY_DIMENSION),
        NUL("us to that scary dimension?"),
        "position(blue,below)",
        "speak_active",

        "squeak(blue)",
        "changetile(blue,150)", //upside down frown :(
        "text(blue,0,0,1)",
        IDC("What happened?", STRC_TALKBLUE_7_WHAT_HAPPENED),
        "position(blue,below)",
        "speak_active",

        "squeak(player)",
        "text(player,0,0,1)",
        IDC("I don't know, Doctor...", STRC_TALKBLUE_7_DONT_KNOW),
        "position(player,above)",
        "speak_active",

        "squeak(cry)",
        "changetile(blue,150)", //upside down frown :(
        "text(blue,0,0,1)",
        IDC("Why?", STRC_TALKBLUE_7_WHY),
        "position(blue,below)",
        "speak_active",

        "endtext",

        "endcutscene()",
        "untilbars()",
        "createactivityzone(blue)",
        };
        filllines(lines);
    }
    else if (SDL_strcmp(t, "talkblue_8") == 0)
    {
        static const char* lines[] = {
        "cutscene()",
        "untilbars()",
        "face(player,blue)",
        "face(blue,player)",

        "squeak(blue)",
        "changetile(blue,6)", //smiling again! blue always needs to specify her mood
        "text(blue,0,0,1)",
        IDC("Heya Captain!", STRC_TALKBLUE_8_HEYA_CAPTAIN),
        "position(blue,below)",
        "speak_active",

        "squeak(blue)",
        "changetile(blue,6)", //smiling again! blue always needs to specify her mood
        "text(blue,0,0,3)",
        IDC("Are you going to try", STRC_TALKBLUE_8_FIND_SHINY_THINGS),
        NUL("and find the rest of"),
        NUL("these shiny things?"),
        "position(blue,below)",
        "speak_active",

        "endtext",

        "endcutscene()",
        "untilbars()",
        "createactivityzone(blue)",
        };
        filllines(lines);
    }
    else if (SDL_strcmp(t, "talkblue_9") == 0)
    {
        static const char* lines[] = {
        "cutscene()",
        "untilbars()",
        "face(player,blue)",
        "face(blue,player)",

        "squeak(blue)",
        "text(blue,0,0,3)",
        IDC("This lab is amazing! The scientists", STRC_TALKBLUE_9_LAB_AMAZING),
        NUL("who worked here know a lot more"),
        NUL("about warp technology than we do!"),
        "position(blue,below)",
        "speak_active",
        "endtext",

        "endcutscene()",
        "untilbars()",
        "createactivityzone(blue)",
        };
        filllines(lines);
    }
    else if (SDL_strcmp(t, "talkblue_trinket1") == 0)
    {
        static const char* lines[] = {
        "cutscene()",
        "untilbars()",
        "face(player,blue)",
        "face(blue,player)",

        "squeak(blue)",
        "changetile(blue,6)", //smiling again! blue always needs to specify her mood
        "text(blue,0,0,2)",
        IDC("Hey Captain, I found", STRC_TALKBLUE_TRINKET1_FOUND_THIS),
        NUL("this in that lab..."),
        "position(blue,below)",
        "speak_active",

        "endtext",
        "delay(30)",

        //found a trinket!
        "foundtrinket(18)",
        "endtext",
        "musicfadein",

        "delay(30)",
        "createentity(136,80,22,18,0)",

        "squeak(blue)",
        "changetile(blue,6)", //smiling again! blue always needs to specify her mood
        "text(blue,0,0,1)",
        IDC("Any idea what it does?", STRC_TALKBLUE_TRINKET1_ANY_IDEA_WHAT),
        "position(blue,below)",
        "speak_active",

        "squeak(player)",
        "text(player,0,0,1)",
        IDC("Sorry, I don't know!", STRC_TALKBLUE_TRINKET1_DONT_KNOW),
        "position(player,above)",
        "speak_active",

        "squeak(player)",
        "text(player,0,0,1)",
        IDC("They seem important, though...", STRC_TALKBLUE_TRINKET1_SEEM_IMPORTANT),
        "position(player,above)",
        "speak_active",

        "squeak(player)",
        "text(player,0,0,2)",
        IDC("Maybe something will happen", STRC_TALKBLUE_TRINKET1_FIND_ALL),
        "if we find them all?",
        "position(player,above)",
        "speak_active",

        "endtext",

        "endcutscene()",
        "untilbars()",
        "createactivityzone(blue)",
        };
        filllines(lines);
    }
    else if (SDL_strcmp(t, "talkblue_trinket2") == 0)
    {
        static const char* lines[] = {
        "cutscene()",
        "untilbars()",
        "face(player,blue)",
        "face(blue,player)",

        "squeak(blue)",
        "changetile(blue,6)", //smiling again! blue always needs to specify her mood
        "text(blue,0,0,3)",
        IDC("Captain! Come have a", STRC_TALKBLUE_TRINKET2_LOOK_WORKING_ON),
        NUL("look at what I've"),
        NUL("been working on!"),
        "position(blue,below)",
        "speak_active",

        "squeak(blue)",
        "changetile(blue,6)", //smiling again! blue always needs to specify her mood
        "text(blue,0,0,3)",
        IDC("It looks like these shiny", STRC_TALKBLUE_TRINKET2_ENERGY_READING),
        NUL("things are giving off a"),
        NUL("strange energy reading!"),
        "position(blue,below)",
        "speak_active",

        "squeak(blue)",
        "changetile(blue,6)", //smiling again! blue always needs to specify her mood
        "text(blue,0,0,1)",
        IDC("So I analysed it...", STRC_TALKBLUE_TRINKET2_ANALYSED),
        "position(blue,below)",
        "speak_active",

        "trinketbluecontrol()",
        };
        filllines(lines);
    }
    else if (SDL_strcmp(t, "talkblue_trinket3") == 0)
    {
        //If you missed the first conversation
        static const char* lines[] = {
        "cutscene()",
        "untilbars()",
        "face(player,blue)",
        "face(blue,player)",

        "squeak(blue)",
        "changetile(blue,6)", //smiling again! blue always needs to specify her mood
        "text(blue,0,0,3)",
        IDC("Captain! Come have a", STRC_TALKBLUE_TRINKET3_LOOK_WORKING_ON),
        NUL("look at what I've"),
        NUL("been working on!"),
        "position(blue,below)",
        "speak_active",

        "squeak(blue)",
        "changetile(blue,6)", //smiling again! blue always needs to specify her mood
        "text(blue,0,0,1)",
        IDC("I found this in that lab...", STRC_TALKBLUE_TRINKET3_FOUND_THIS),
        "position(blue,below)",
        "speak_active",

        "endtext",
        "delay(30)",

        //found a trinket!
        "foundtrinket(18)",
        "endtext",
        "musicfadein",

        "delay(30)",
        "createentity(136,80,22,18,0)",

        "squeak(blue)",
        "changetile(blue,6)", //smiling again! blue always needs to specify her mood
        "text(blue,0,0,3)",
        IDC("It seemed to be", STRC_TALKBLUE_TRINKET3_ENERGY_READING),
        NUL("giving off a weird"),
        NUL("energy reading..."),
        "position(blue,below)",
        "speak_active",

        "squeak(blue)",
        "changetile(blue,6)", //smiling again! blue always needs to specify her mood
        "text(blue,0,0,1)",
        IDC("So I analysed it...", STRC_TALKBLUE_TRINKET3_ANALYSED),
        "position(blue,below)",
        "speak_active",

        "trinketbluecontrol()",
        };
        filllines(lines);
    }
    else if (SDL_strcmp(t, "talkblue_trinket4") == 0)
    {
        static const char* lines[] = {
        "hidetrinkets()",
        "endtextfast",
        "delay(10)",

        //add map mode here and wrap up...
        "gamemode(teleporter)",
        "delay(20)",

        "squeak(blue)",
        "text(blue,50,15,2)",
        IDC("...and I was able to find more", STRC_TALKBLUE_TRINKET4_ABLE_FIND_MORE),
        NUL("of them with the ship's scanner!"),
        "speak_active",

        "endtext",

        "squeak(terminal)",
        "showtrinkets()",
        "delay(10)",
        "hidetrinkets()",
        "delay(10)",
        "showtrinkets()",
        "delay(10)",
        "hidetrinkets()",
        "delay(10)",
        "showtrinkets()",
        "delay(75)",

        "gamemode(game)",
        "delay(20)",

        "squeak(blue)",
        "changetile(blue,6)", //smiling again! blue always needs to specify her mood
        "text(blue,0,0,3)",
        IDC("If you get a chance, it", STRC_TALKBLUE_TRINKET4_FIND_REST),
        NUL("might be worth finding"),
        "the rest of them!",
        "position(blue,below)",
        "speak_active",

        "squeak(cry)",
        "changetile(blue,150)", //upside down frown :(
        "text(blue,0,0,2)",
        IDC("Don't put yourself in", STRC_TALKBLUE_TRINKET4_DONT_DANGER),
        NUL("any danger, though!"),
        "position(blue,below)",
        "speak_active",

        "endtext",

        "endcutscene()",
        "untilbars()",
        "createactivityzone(blue)",
        };
        filllines(lines);
    }
    else if (SDL_strcmp(t, "talkblue_trinket5") == 0)
    {
        static const char* lines[] = {
        "squeak(blue)",
        "changetile(blue,6)", //smiling again! blue always needs to specify her mood
        "text(blue,0,0,3)",
        IDC("...but it looks like you've", STRC_TALKBLUE_TRINKET5_FOUND_ALL),
        NUL("already found all of them"),
        NUL("in this dimension!"),
        "position(blue,below)",
        "speak_active",

        "squeak(player)",
        "text(player,0,0,1)",
        IDC("Oh? Really?", STRC_TALKBLUE_TRINKET5_OH_REALLY),
        "position(player,above)",
        "speak_active",

        "squeak(blue)",
        "changetile(blue,6)", //smiling again! blue always needs to specify her mood
        "text(blue,0,0,2)",
        IDC("Yeah, well done! That", STRC_TALKBLUE_TRINKET5_WELL_DONE),
        NUL("can't have been easy!"),
        "position(blue,below)",
        "speak_active",

        "endtext",

        "endcutscene()",
        "untilbars()",
        "createactivityzone(blue)",
        };
        filllines(lines);
    }
    else if (SDL_strcmp(t, "talkblue_trinket6") == 0)
    {
        static const char* lines[] = {
        "squeak(blue)",
        "changetile(blue,6)", //smiling again! blue always needs to specify her mood
        "text(blue,0,0,3)",
        IDC("...and they're related.", STRC_TALKBLUE_TRINKET6_THEYRE_RELATED),
        NUL("They're all a part of"),
        NUL("something bigger!"),
        "position(blue,below)",
        "speak_active",

        "squeak(player)",
        "text(player,0,0,1)",
        IDC("Oh? Really?", STRC_TALKBLUE_TRINKET6_OH_REALLY),
        "position(player,above)",
        "speak_active",

        "squeak(blue)",
        "changetile(blue,6)", //smiling again! blue always needs to specify her mood
        "text(blue,0,0,4)",
        IDC("Yeah! There seem to be", STRC_TALKBLUE_TRINKET6_SEEM_TO_BE_20),
        NUL("twenty variations of"),
        NUL("the fundamental energy"),
        NUL("signature..."),
        "position(blue,below)",
        "speak_active",

        "squeak(blue)",
        "changetile(blue,6)", //smiling again! blue always needs to specify her mood
        "text(blue,0,0,1)",
        IDC("Wait...", STRC_TALKBLUE_TRINKET6_WAIT),
        "position(blue,below)",
        "speak_active",

        "squeak(blue)",
        "changetile(blue,6)", //smiling again! blue always needs to specify her mood
        "text(blue,0,0,2)",
        IDC("Does that mean you've", STRC_TALKBLUE_TRINKET6_FOUND_ALL),
        NUL("found all of them?"),
        "position(blue,below)",
        "speak_active",

        "endtext",

        "loadscript(startepilogue)",
        };
        filllines(lines);
    }
    else if (SDL_strcmp(t, "talkyellow_trinket1") == 0)
    {
        static const char* lines[] = {
        "cutscene()",
        "untilbars()",
        "face(player,yellow)",
        "face(yellow,player)",

        "squeak(yellow)",
        "text(yellow,0,0,2)",
        IDC("Captain! I've been meaning", STRC_TALKYELLOW_TRINKET1_GIVE_TO_YOU),
        NUL("to give this to you..."),
        "position(yellow,above)",
        "speak_active",
        "endtext",

        "delay(30)",

        //found a trinket!
        "foundtrinket(18)",
        "endtext",
        "musicfadein",

        "delay(30)",

        "squeak(player)",
        "text(player,0,0,1)",
        IDC("Professor! Where did you find this?", STRC_TALKYELLOW_TRINKET1_WHERE_FIND),
        "position(player,above)",
        "speak_active",

        "squeak(yellow)",
        "text(yellow,0,0,2)",
        IDC("Oh, it was just lying", STRC_TALKYELLOW_TRINKET1_LYING_AROUND),
        NUL("around that space station."),
        "position(yellow,above)",
        "speak_active",

        "squeak(cry)",
        "changemood(yellow,1)",
        "text(yellow,0,0,3)",
        IDC("It's a pity Doctor Victoria", STRC_TALKYELLOW_TRINKET1_VICTORIA_NOT_HERE),
        NUL("isn't here, she loves studying"),
        NUL("that sort of thing..."),
        "position(yellow,above)",
        "speak_active",

        "squeak(player)",
        "text(player,0,0,1)",
        IDC("Any idea what it does?", STRC_TALKYELLOW_TRINKET1_ANY_IDEA_WHAT),
        "position(player,above)",
        "speak_active",

        "squeak(yellow)",
        "changemood(yellow,0)",
        "text(yellow,0,0,2)",
        IDC("Nope! But it is giving off", STRC_TALKYELLOW_TRINKET1_ENERGY_READING),
        NUL("a strange energy reading..."),
        "position(yellow,above)",
        "speak_active",
        "endtext",

        "trinketyellowcontrol()",
        };
        filllines(lines);
    }
    else if (SDL_strcmp(t, "talkyellow_trinket2") == 0)
    {
        static const char* lines[] = {
        "hidetrinkets()",
        "endtextfast",
        "delay(10)",

        //add map mode here and wrap up...
        "gamemode(teleporter)",
        "delay(20)",

        "squeak(yellow)",
        "text(yellow,50,15,2)",
        IDC("...so I used the ship's scanner", STRC_TALKYELLOW_TRINKET2_FIND_MORE),
        NUL("to find more of them!"),
        "speak_active",

        "endtext",

        "squeak(terminal)",
        "showtrinkets()",
        "delay(10)",
        "hidetrinkets()",
        "delay(10)",
        "showtrinkets()",
        "delay(10)",
        "hidetrinkets()",
        "delay(10)",
        "showtrinkets()",
        "delay(75)",

        "gamemode(game)",
        "delay(20)",

        "squeak(yellow)",
        "changemood(yellow,0)",
        "text(yellow,0,0,3)",
        IDC("...Please don't let them", STRC_TALKYELLOW_TRINKET2_DONT_DISTRACT),
        NUL("distract you from finding"),
        NUL("Victoria, though!"),
        "position(yellow,above)",
        "speak_active",

        "squeak(yellow)",
        "text(yellow,0,0,1)",
        IDC("I hope she's ok...", STRC_TALKYELLOW_TRINKET2_HOPE_SHES_OK),
        "position(yellow,above)",
        "speak_active",

        "endtext",

        "endcutscene()",
        "untilbars()",
        "createactivityzone(yellow)",
        };
        filllines(lines);
    }
    else if (SDL_strcmp(t, "talkyellow_trinket3") == 0)
    {
        static const char* lines[] = {
        "squeak(yellow)",
        "changemood(yellow,0)",
        "text(yellow,0,0,2)",
        IDC("Can't seem to detect any", STRC_TALKYELLOW_TRINKET3_CANT_DETECT_MORE),
        NUL("more of them nearby, though."),
        "position(yellow,above)",
        "speak_active",

        "squeak(yellow)",
        "changemood(yellow,0)",
        "text(yellow,0,0,1)",
        IDC("Maybe you've found them all?", STRC_TALKYELLOW_TRINKET3_FOUND_ALL),
        "position(yellow,above)",
        "speak_active",
        "endtext",

        "endcutscene()",
        "untilbars()",
        "createactivityzone(yellow)",
        };
        filllines(lines);
    }
    else if (SDL_strcmp(t, "gamecomplete") == 0)
    {
        static const char* lines[] = {
        "gotoroom(2,11)",
        "gotoposition(160,120,0)",
        "nocontrol()",
        "createcrewman(185,153,purple,0,faceleft)",
        "createcrewman(205,153,yellow,0,faceleft)",
        "createcrewman(225,153,red,0,faceleft)",
        "createcrewman(245,153,green,0,faceleft)",
        "createcrewman(265,153,blue,1,faceleft)",

        "cutscene()",
        "untilbars()",

        "delay(30)",
        "rescued(player)",

        "squeak(yellow)",
        "text(yellow,0,0,1)",
        IDC("Any moment now...", STRC_GAMECOMPLETE_ANY_MOMENT),
        "position(yellow,above)",
        "speak_active",
        "endtext",
        "nocontrol()",

        "delay(60)",

        "gamestate(4080)",
        };
        filllines(lines);
    }
    else if (SDL_strcmp(t, "gamecomplete_ending") == 0)
    {
        const char* lines[] = {
        "delay(15)",
        "changemood(blue,0)",
        "play(10)",
        "delay(45)",

        "squeak(player)",
        "text(player,0,0,1)",
        IDC("Hello!", STRC_GAMECOMPLETE_END_HELLO),
        "position(player,above)",
        "speak_active",
        "endtext",

        "squeak(purple)",
        "delay(1)",
        "squeak(yellow)",
        "delay(1)",
        "squeak(red)",
        "delay(1)",
        "squeak(green)",

        "textcase(1)",
        "text(purple,0,0,1)",
        IDC("Captain!        ", STRC_GAMECOMPLETE_END_PURPLE_CAPTAIN),
        "position(purple,above)",
        "backgroundtext",
        "speak",
        "textcase(2)",
        "text(yellow,0,0,1)",
        IDC("Captain!      ", STRC_GAMECOMPLETE_END_YELLOW_CAPTAIN),
        "position(yellow,above)",
        "backgroundtext",
        "speak",
        "textcase(3)",
        "text(red,0,0,1)",
        IDC("Captain!    ", STRC_GAMECOMPLETE_END_RED_CAPTAIN),
        "position(red,above)",
        "backgroundtext",
        "speak",
        "textcase(4)",
        "text(green,0,0,1)",
        IDC("Captain!  ", STRC_GAMECOMPLETE_END_GREEN_CAPTAIN),
        "position(green,above)",
        "backgroundtext",
        "speak",
        "textcase(5)",
        "text(blue,0,0,1)",
        IDC("Captain!", STRC_GAMECOMPLETE_END_BLUE_CAPTAIN),
        "position(blue,above)",
        "speak",

        "endtextfast",

        "squeak(blue)",
        "text(blue,0,0,1)",
        IDC("You're alright!", STRC_GAMECOMPLETE_END_YOURE_ALRIGHT),
        "position(blue,above)",
        "speak_active",

        "squeak(blue)",
        "text(blue,0,0,1)",
        IDC("I knew you'd be ok!", STRC_GAMECOMPLETE_END_KNEW_YOUD_BE_OK),
        "position(blue,above)",
        "speak_active",

        "squeak(purple)",
        "text(purple,0,0,2)",
        IDC("We were very worried when", STRC_GAMECOMPLETE_END_WORRIED_DIDNT_COME),
        NUL("you didn't come back..."),
        "position(purple,above)",
        "speak_active",

        "squeak(green)",
        "text(green,0,0,3)",
        IDC("...but when you turned", STRC_GAMECOMPLETE_END_TURNED_OFF_SOURCE),
        NUL("off the source of"),
        NUL("the interference..."),
        "position(green,above)",
        "speak_active",

        "squeak(yellow)",
        "text(yellow,0,0,3)",
        IDC("...we were able to", STRC_GAMECOMPLETE_END_FIND_YOU_SCANNERS),
        NUL("find you with the"),
        NUL("ship's scanners..."),
        "position(yellow,above)",
        "speak_active",

        "squeak(red)",
        "text(red,0,0,2)",
        IDC("...and teleport you", STRC_GAMECOMPLETE_END_TELEPORT_YOU),
        NUL("back on board!"),
        "position(red,above)",
        "speak_active",

        "squeak(player)",
        "text(player,0,0,1)",
        IDC("That was lucky!", STRC_GAMECOMPLETE_END_WAS_LUCKY),
        "Thanks guys!",
        "position(player,above)",
        "speak_active",

        "squeak(player)",
        "text(player,0,0,1)",
        IDC("Thanks guys!", STRC_GAMECOMPLETE_END_THANKS_GUYS),
        "position(player,above)",
        "speak_active",

        "endtext",

        //Move to Vitellary's lab
        "fadeout()",
        "untilfade()",

        "missing(purple)",
        "missing(red)",
        "missing(green)",
        "missing(blue)",
        "missing(yellow)",

        "gotoroom(3,11)",
        "gotoposition(117,105,0)",
        "changedir(player,0)",
        "createcrewman(75,105,yellow,0,faceright)",
        "createcrewman(190,105,red,0,faceleft)",

        "fadein()",
        "untilfade()",

        "squeak(yellow)",
        "text(yellow,0,0,4)",
        IDC("...it looks like this", STRC_GAMECOMPLETE_END_DESTABILISE),
        NUL("dimension is starting"),
        NUL("to destabilise, just"),
        NUL("like our own..."),
        "position(yellow,above)",
        "speak_active",

        "walk(right,3)",

        "squeak(red)",
        "text(red,0,0,3)",
        IDC("...we can stay and", STRC_GAMECOMPLETE_END_EXPLORE_A_LITTLE),
        NUL("explore for a little"),
        NUL("longer, but..."),
        "position(red,above)",
        "speak_active",

        "walk(left,3)",

        "squeak(yellow)",
        "text(yellow,0,0,2)",
        IDC("...eventually, it'll", STRC_GAMECOMPLETE_END_COLLAPSE_COMPLETELY),
        NUL("collapse completely."),
        "position(yellow,above)",
        "speak_active",

        "endtext",

        //Move to Vertigris' lab
        "fadeout()",
        "untilfade()",

        "gotoroom(3,10)",
        "gotoposition(210,177,0)",
        "changedir(player,1)",
        "createcrewman(245,177,green,0,faceleft)",
        "createcrewman(56,177,blue,0,faceright)",

        "fadein()",
        "untilfade()",

        "squeak(green)",
        "text(green,0,0,3)",
        IDC("There's no telling exactly", STRC_GAMECOMPLETE_END_HOW_LONG),
        NUL("how long we have here. But"),
        NUL("the ship's fixed, so..."),
        "position(green,above)",
        "speak_active",

        "walk(left,3)",

        "squeak(blue)",
        "text(blue,0,0,2)",
        IDC("...as soon as we're", STRC_GAMECOMPLETE_END_WE_CAN_GO_HOME),
        NUL("ready, we can go home!"),
        "position(blue,above)",
        "speak_active",

        "endtext",

        //Move to the bridge!
        "fadeout()",
        "untilfade()",

        "gotoroom(4,10)",
        "gotoposition(227,113,0)",
        "changedir(player,0)",
        "createcrewman(140,177,purple,0,faceright)",
        "createcrewman(115,177,yellow,0,faceright)",
        "createcrewman(90,177,red,0,faceright)",
        "createcrewman(65,177,green,0,faceright)",
        "createcrewman(40,177,blue,0,faceright)",

        "rescued(purple)",
        "rescued(red)",
        "rescued(green)",
        "rescued(blue)",
        "rescued(yellow)",

        "fadein()",
        "untilfade()",

        "squeak(purple)",
        "text(purple,0,0,1)",
        IDC("What now, Captain?", STRC_GAMECOMPLETE_END_WHAT_NOW_CAPTAIN),
        "position(purple,above)",
        "speak_active",

        "squeak(player)",
        "text(player,0,0,2)",
        IDC("Let's find a way to save", STRC_GAMECOMPLETE_END_SAVE_THIS_DIMENSION),
        NUL("this dimension!"),
        "position(player,above)",
        "speak_active",

        "squeak(player)",
        "text(player,0,0,2)",
        IDC("And a way to save our", STRC_GAMECOMPLETE_END_SAVE_HOME_DIMENSION),
        NUL("home dimension too!"),
        "position(player,above)",
        "speak_active",

        "squeak(player)",
        "text(player,0,0,1)",
        IDC("The answer is out there, somewhere!", STRC_GAMECOMPLETE_END_ANSWER_OUT_THERE),
        "position(player,above)",
        "speak_active",
        "endtext",

        "delay(30)",

        "squeak(player)",
        "text(player,0,0,1)",
        IDC("Let's go!", STRC_GAMECOMPLETE_END_LETS_GO),
        "position(player,above)",
        "speak_active",

        "endtext",

        "fadeout()",
        "untilfade()",
        "rollcredits()",
        };
        filllines(lines);
    }
    else if (SDL_strcmp(t, "startepilogue") == 0)
    {
        static const char* lines[] = {
        "cutscene()",
        "untilbars()",
        "face(player,blue)",
        "face(blue,player)",

        "squeak(blue)",
        "changetile(blue,6)", //smiling again! blue always needs to specify her mood
        "text(blue,0,0,1)",
        IDC("Wow! You found all of them!", STRC_STARTEPILOGUE_FOUND_ALL),
        "position(blue,below)",
        "speak_active",

        "squeak(player)",
        "text(player,0,0,1)",
        IDC("Really? Great!", STRC_STARTEPILOGUE_REALLY_GREAT),
        "position(player,above)",
        "speak_active",

        "squeak(blue)",
        "changetile(blue,6)", //smiling again! blue always needs to specify her mood
        "text(blue,0,0,3)",
        IDC("I'll run some tests and", STRC_STARTEPILOGUE_RUN_SOME_TESTS),
        NUL("see if I can work out"),
        NUL("what they're for..."),
        "position(blue,below)",
        "speak_active",

        "endtext",

        "flash(5)",
        "shake(20)",
        "playef(9)",

        "musicfadeout()",

        "delay(30)",

        "squeak(cry)",
        "changemood(player,1)",
        "changetile(blue,150)", //upside down frown :(
        "text(player,0,0,2)",
        IDC("That... that didn't", STRC_STARTEPILOGUE_DIDNT_SOUND_GOOD),
        NUL("sound good..."),
        "position(player,above)",
        "speak_active",

        "endtext",

        "delay(30)",

        "flash(5)",
        "shake(20)",
        "playef(9)",
        "alarmon",

        "delay(30)",

        "squeak(cry)",
        "text(blue,0,0,1)",
        IDC("Run!", STRC_STARTEPILOGUE_RUN),
        "position(blue,below)",
        "speak_active",
        "endtext",

        "delay(5)",

        "missing(green)",
        "missing(yellow)",

        "flash(5)",
        "shake(50)",
        "playef(9)",
        "gotoroom(3,10)",
        "gotoposition(40,177,0)",
        "createcrewman(208,177,green,1,followposition,120)",
        "createcrewman(240,177,purple,1,followposition,120)",
        "createcrewman(10,177,blue,1,followposition,180)",

        "squeak(player)",
        "text(player,80,150,1)",
        IDC("Oh no!", STRC_STARTEPILOGUE_OH_NO),
        "backgroundtext",
        "speak_active",
        "walk(right,20)",

        "endtextfast",

        //and the next!
        "flash(5)",
        "shake(50)",
        "playef(9)",
        "gotoroom(3,11)",
        "gotoposition(140,0,0)",

        "createcrewman(90,105,green,1,followblue)",
        "createcrewman(125,105,purple,1,followgreen)",
        "createcrewman(55,105,blue,1,followposition,-200)",

        "createcrewman(120,177,yellow,1,followposition,-200)",
        "createcrewman(240,177,red,1,faceleft)",

        "delay(5)",
        "changeai(red,followposition,-200)",

        "squeak(red)",
        "text(red,100,150,1)",
        IDC("Not again!", STRC_STARTEPILOGUE_NOT_AGAIN),
        "backgroundtext",
        "speak_active",

        "walk(left,25)",

        "endtextfast",

        //final room:
        "flash(5)",
        "alarmoff",
        "playef(9)",
        "gotoroom(2,11)",
        "gotoposition(265,153,0)",

        "createcrewman(130,153,blue,1,faceleft)",
        "createcrewman(155,153,green,1,faceleft)",
        "createcrewman(180,153,purple,1,faceleft)",
        "createcrewman(205,153,yellow,1,faceleft)",
        "createcrewman(230,153,red,1,faceleft)",

        "delay(75)",

        "squeak(player)",
        "changemood(player,0)",
        "text(player,0,0,1)",
        IDC("Wait! It's stopped!", STRC_STARTEPILOGUE_ITS_STOPPED),
        "position(player,above)",
        "speak_active",
        "endtext",

        "delay(30)",
        "changemood(purple,0)",
        "changedir(purple,1)",
        "changemood(red,0)",
        "changedir(red,1)",
        "changemood(green,0)",
        "changedir(green,1)",
        "changemood(blue,0)",
        "changedir(blue,1)",
        "changemood(yellow,0)",
        "changedir(yellow,1)",
        "delay(30)",

        "rescued(green)",
        "rescued(yellow)",
        "missing(blue)",
        "altstates(1)",

        "fadeout()",
        "untilfade()",

        "gotoroom(2,10)",
        "gotoposition(227,113,0)",
        "changedir(player,0)",

        "rescued(blue)",

        "createcrewman(150,177,purple,0,faceleft)",
        "createcrewman(90,177,yellow,0,faceright)",
        "createcrewman(184,185,red,0,faceleft)",
        "createcrewman(65,177,green,0,faceright)",
        "createcrewman(35,177,blue,0,faceright)",

        "rescued(purple)",
        "rescued(red)",
        "rescued(green)",
        "rescued(yellow)",

        "fadein()",
        "untilfade()",

        "delay(30)",

        "squeak(purple)",
        "text(purple,0,0,3)",
        IDC("This is where we were", STRC_STARTEPILOGUE_WHERE_STORING_SHINY),
        NUL("storing those shiny"),
        NUL("things? What happened?"),
        "position(purple,above)",
        "speak_active",

        "squeak(player)",
        "text(player,0,0,2)",
        IDC("We were just playing", STRC_STARTEPILOGUE_PLAYING_AND),
        NUL("with them, and..."),
        "position(player,above)",
        "speak_active",
        "endtext",

        "squeak(cry)",
        "changemood(player,1)",
        "text(player,0,0,1)",
        IDC("...they suddenly exploded!", STRC_STARTEPILOGUE_EXPLODED),
        "position(player,above)",
        "speak_active",
        "endtext",

        "squeak(blue)",
        "text(blue,0,0,2)",
        IDC("But look what they made!", STRC_STARTEPILOGUE_IS_THAT_TELE),
        NUL("Is that a teleporter?"),
        "position(blue,above)",
        "speak_active",

        "squeak(yellow)",
        "text(yellow,0,0,1)",
        IDC("I think so, but...", STRC_STARTEPILOGUE_THINK_SO),
        "position(yellow,above)",
        "speak_active",

        "squeak(yellow)",
        "text(yellow,0,0,2)",
        IDC("I've never seen a teleporter", STRC_STARTEPILOGUE_NEVER_SEEN_LIKE_THAT),
        NUL("like that before..."),
        "position(yellow,above)",
        "speak_active",
        "endtext",

        "changemood(player,0)",

        "delay(30)",

        "squeak(red)",
        "text(red,0,0,1)",
        IDC("We should investigate!", STRC_STARTEPILOGUE_INVESTIGATE),
        "position(red,above)",
        "speak_active",

        "squeak(purple)",
        "text(purple,0,0,1)",
        IDC("What do you think, Captain?", STRC_STARTEPILOGUE_WHAT_THINK_CAPTAIN),
        "position(purple,above)",
        "speak_active",

        "squeak(purple)",
        "text(purple,0,0,2)",
        IDC("Should we find out", STRC_STARTEPILOGUE_FIND_WHERE_LEADS),
        NUL("where it leads?"),
        "position(purple,above)",
        "speak_active",
        "endtext",

        "delay(15)",

        "squeak(player)",
        "text(player,0,0,1)",
        IDC("Let's go!", STRC_STARTEPILOGUE_LETS_GO),
        "position(player,above)",
        "speak_active",
        "endtext",

        "walk(left,10)",
        "flip",
        "walk(left,5)",

        "flash(5)",
        "shake(20)",
        "playef(10)",
        "blackout()",

        "delay(45)",

        "gotoroom(17,6)",
        "gotoposition(80,109,1)",
        "changedir(player,1)",
        "flash(5)",
        "shake(20)",
        "playef(10)",
        "blackon()",

        "delay(15)",
        "flash(5)",
        "shake(20)",
        "playef(10)",
        "createcrewman(28,65,purple,0,faceright)",

        "delay(15)",
        "flash(5)",
        "shake(20)",
        "playef(10)",
        "createcrewman(145,169,yellow,0,faceleft)",

        "delay(15)",
        "flash(5)",
        "shake(20)",
        "playef(10)",
        "createcrewman(32,169,red,0,faceright)",

        "delay(15)",
        "flash(5)",
        "shake(20)",
        "playef(10)",
        "createcrewman(96,149,green,0,faceleft)",

        "delay(15)",
        "flash(5)",
        "shake(20)",
        "playef(10)",
        "createcrewman(155,57,blue,0,faceleft)",

        "delay(45)",


        "squeak(cry)",
        "changemood(blue,1)",
        "text(blue,0,0,1)",
        IDC("Oh no! We're trapped!", STRC_STARTEPILOGUE_OH_NO_WERE_TRAPPED),
        "position(blue,above)",
        "speak_active",

        "squeak(cry)",
        "changemood(yellow,1)",
        "text(yellow,0,0,1)",
        IDC("Oh dear...", STRC_STARTEPILOGUE_OH_DEAR),
        "position(yellow,above)",
        "speak_active",

        "squeak(cry)",
        "changemood(red,1)",
        "changemood(green,1)",
        "changemood(purple,1)",
        "changemood(player,1)",
        "text(player,0,0,2)",
        IDC("Hmm... how should we", STRC_STARTEPILOGUE_HOW_GET_OUT),
        NUL("get out of this?"),
        "position(player,below)",
        "speak_active",

        "endtext",

        "delay(70)",

        "squeak(purple)",
        "delay(1)",
        "squeak(yellow)",
        "delay(1)",
        "squeak(red)",
        "delay(1)",
        "squeak(blue)",
        "delay(1)",
        "squeak(player)",
        "delay(1)",
        "squeak(green)",

        "changemood(yellow,0)",
        "changemood(blue,0)",
        "changemood(red,0)",
        "changemood(player,0)",
        "changemood(green,0)",
        "changemood(purple,0)",
        "textcase(1)",
        "text(player,0,0,1)",
        IDC("COMBINE!", STRC_STARTEPILOGUE_PLAYER_COMBINE),
        "position(player,above)",
        "backgroundtext",
        "speak",
        "textcase(2)",
        "text(purple,0,0,1)",
        IDC("COMBINE!", STRC_STARTEPILOGUE_PURPLE_COMBINE),
        "position(purple,above)",
        "backgroundtext",
        "speak",
        "textcase(3)",
        "text(yellow,0,0,1)",
        IDC("COMBINE!", STRC_STARTEPILOGUE_YELLOW_COMBINE),
        "position(yellow,above)",
        "backgroundtext",
        "speak",
        "textcase(4)",
        "text(red,0,0,1)",
        IDC("COMBINE!", STRC_STARTEPILOGUE_RED_COMBINE),
        "position(red,above)",
        "backgroundtext",
        "speak",
        "textcase(5)",
        "text(green,0,0,1)",
        IDC("COMBINE!", STRC_STARTEPILOGUE_GREEN_COMBINE),
        "position(green,above)",
        "backgroundtext",
        "speak",
        "textcase(6)",
        "text(blue,0,0,1)",
        IDC("COMBINE!", STRC_STARTEPILOGUE_BLUE_COMBINE),
        "position(blue,above)",
        "speak",

        "endtextfast",

        "delay(15)",
        "flip",
        "changeai(purple,followplayer)",
        "changeai(blue,followplayer)",
        "changeai(red,followplayer)",
        "changeai(yellow,followplayer)",
        "changeai(green,followplayer)",
        "walk(right,3)",

        "delay(5)",
        "flash(10)",
        "shake(20)",
        "playef(24)",
        "gotoroom(17,6)",
        "vvvvvvman()",


        "delay(90)",


        "walk(right,6)",
        "flash(10)",
        "shake(20)",
        "playef(23)",
        "altstates(2)",
        "gotoroom(17,6)",

        "delay(20)",

        "walk(right,12)",
        "flash(10)",
        "shake(20)",
        "playef(23)",
        "altstates(0)",
        "gotoroom(17,6)",

        "delay(20)",

        "walk(right,15)",

        "gotoroom(18,6)",
        "gotoposition(0,46,0)",
        "walk(right,5)",

        "delay(20)",
        "flash(10)",
        "shake(20)",
        "playef(24)",
        "undovvvvvvman()",
        "createcrewman(30,99,purple,0,faceright)",
        "createcrewman(65,119,yellow,0,faceright)",
        "createcrewman(135,149,red,0,faceleft)",
        "createcrewman(170,159,green,0,faceleft)",
        "createcrewman(205,159,blue,0,faceleft)",


        "delay(60)",


        "changedir(yellow,0)",
        "changedir(player,0)",
        "delay(20)",
        "squeak(purple)",
        "text(purple,0,0,3)",
        IDC("Or, you know... we could", STRC_STARTEPILOGUE_COULD_HAVE_WARPED),
        NUL("have just warped back"),
        NUL("to the ship..."),
        "position(purple,above)",
        "speak_active",

        "endtext",

        "delay(30)",

        "changedir(purple,1)",
        "changedir(yellow,1)",
        "changedir(player,1)",
        "changedir(red,1)",

        "changedir(green,1)",
        "squeak(green)",
        "text(green,0,0,1)",
        IDC("Wow! What is this?", STRC_STARTEPILOGUE_WOW_WHAT_THIS),
        "position(green,above)",
        "speak_active",


        "changedir(purple,1)",
        "changedir(yellow,1)",
        "changedir(player,0)",
        "changedir(red,0)",
        "changedir(green,0)",
        "squeak(yellow)",
        "text(yellow,0,0,1)",
        IDC("It looks like another laboratory!", STRC_STARTEPILOGUE_ANOTHER_LAB),
        "position(yellow,above)",
        "speak_active",

        "changedir(purple,1)",
        "changedir(yellow,1)",
        "changedir(player,1)",
        "squeak(red)",
        "text(red,0,0,1)",
        IDC("Let's have a look around!", STRC_STARTEPILOGUE_LOOK_AROUND),
        "position(red,above)",
        "speak_active",

        "endtext",

        "delay(20)",
        "changeai(yellow,followposition,500)",
        "changeai(purple,followposition,500)",
        "changeai(blue,followposition,500)",
        "changeai(red,followposition,500)",
        "changeai(green,followposition,500)",

        "delay(21)",
        "changeai(yellow,faceright)",
        "flipgravity(yellow)",
        "playef(0)",
        "delay(2)",
        "changeai(purple,faceright)",
        "flipgravity(purple)",
        "playef(0)",

        "delay(48)",

        "foundlab",
        "endtext",
        "foundlab2",
        "endtext",

        "entersecretlab",
        "play(11)",

        "endcutscene()",
        "untilbars()",
        };
        filllines(lines);
    }
    else if (SDL_strcmp(t, "returntolab") == 0)
    {
        //To get back to the lab from the gravitron
        static const char* lines[] = {
        "gotoroom(19,7)",
        "gotoposition(132,137,0)",
        "fadein()",

        "setcheckpoint()",

        "play(11)",
        "endcutscene()",
        "untilbars()",
        };
        filllines(lines);
    }
    else if (SDL_strcmp(t, "disableaccessibility") == 0)
    {
        static const char* lines[] = {
        "cutscene()",
        "untilbars()",

        "squeak(terminal)",
        "text(gray,0,114,3)",
        IDC("Please disable invincibility", STRC_DISABLEACCESSIBILITY_SUPERGRAVITRON),
        NUL("and/or slowdown before entering"),
        NUL("the Super Gravitron."),
        "position(center)",
        "speak",

        "endtext",
        "endcutscene()",
        "untilbars()",
        };
        filllines(lines);
    }
    else
    {
        loadother(t);
    }

    return !commands.empty();
}
