#pragma once

#include "winsock.h"
#include "WSnetbs.h"
#include <string.h>
#include <stdio.h>

// Updates patcher signatures (Just signatures)
void updatePatcherSignatures();
// Updates patcher Patchs (Just patches)
void updatePatcherPatches();
// Updates patcher data (Signatures & Patches)
void updatePatcherData();
// Patches studio, studio path being the path to RobloxStudioBeta.exe, createInternalAt being where you want the file to be created, & what you want its name to be.
void PatchStudio(const char* studioPath,const char* createInternalAt);