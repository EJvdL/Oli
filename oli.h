#ifndef OLI_H
#define OLI_H

void oliSetTime(const char* fpString);
void oliSetPassword(const char* fpString);
void oliSetUserSSID(const char* fpString);
void oliSetUserPassword(const char* fpString);
void oliClearSettings();
void oliStoreScenarios();
void oliOnColorPicker(bool);

#endif