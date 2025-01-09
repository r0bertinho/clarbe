#ifndef MESSAGES_H
#define MESSAGES_H

const char HELP_MSG[] =
    "Software usage: \"clarbe <action> [args]?\"\n"
    "\n"
    "clarbe new <project-name>\n"
    "     | init <folder-name>\n"
    "     | add <creator>/<dependency-name>\n"
    "     | remove <creator>/<dependency-name>\n"
    "     | config <placement> <configuration> [values]\n"
    "     | build\n"
    "     | help\n"
    "     | clean\n"
    "     | check\n"
    "     | run\n"
    "--------------------------------\n";

const char VERSION[] = "0.1.0";

#endif