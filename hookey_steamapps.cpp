#include "hookey_common.h"
#include "hookey_steamapps.h"
#include "hookey_impls.h"

typedef std::pair<AppId_t, std::string> DLC;
static std::vector<DLC> dlcs;

bool Hookey_SteamApps_Class::BIsSubscribed() { return true; }
bool Hookey_SteamApps_Class::BIsLowViolence() { return false; }
bool Hookey_SteamApps_Class::BIsCybercafe() { return false; }
bool Hookey_SteamApps_Class::BIsVACBanned() { return false; }
int Hookey_SteamApps_Class::GetDLCCount() { return dlcs.size(); }
bool Hookey_SteamApps_Class::BIsDlcInstalled(AppId_t appID) {
    if (std::find_if(
        std::begin(dlcs),
        std::end(dlcs),
        [&] (const DLC& a) { return a.first == appID; }) != std::end(dlcs)
    ) {
        return true;
    } else {
        return false;
    }
}
bool Hookey_SteamApps_Class::BGetDLCDataByIndex(int iDLC, AppId_t* pAppID, bool* pbAvailable, char* pchName, int cchNameBufferSize) {
    if ((size_t)iDLC >= dlcs.size()) {
        return false;
    }

    *pAppID = dlcs[iDLC].first;
    *pbAvailable = true;

    const char* name = dlcs[iDLC].second.c_str();
    size_t slen = std::min((size_t)cchNameBufferSize - 1, dlcs[iDLC].second.size());
    memcpy((void*)pchName, (void*)name, slen);
    *(pchName + slen) = 0x0;

    return true;
}

const char* Hookey_SteamApps_Class::GetCurrentGameLanguage() { return real_steamApps->GetCurrentGameLanguage(); }
const char* Hookey_SteamApps_Class::GetAvailableGameLanguages() { return real_steamApps->GetAvailableGameLanguages(); }
CSteamID Hookey_SteamApps_Class::GetAppOwner() { return real_steamApps->GetAppOwner(); }
int Hookey_SteamApps_Class::GetAppBuildId() { return real_steamApps->GetAppBuildId(); }
void Hookey_SteamApps_Class::RequestAllProofOfPurchaseKeys() { real_steamApps->RequestAllProofOfPurchaseKeys(); }
bool Hookey_SteamApps_Class::BIsSubscribedFromFamilySharing() { return real_steamApps->BIsSubscribedFromFamilySharing(); }
bool Hookey_SteamApps_Class::BIsSubscribedFromFreeWeekend() { return real_steamApps->BIsSubscribedFromFreeWeekend(); }
bool Hookey_SteamApps_Class::BIsSubscribedApp(AppId_t appID) { return real_steamApps->BIsSubscribedApp(appID); }
bool Hookey_SteamApps_Class::BIsAppInstalled(AppId_t appID) { return real_steamApps->BIsAppInstalled(appID); }
uint32 Hookey_SteamApps_Class::GetEarliestPurchaseUnixTime(AppId_t appID) { return real_steamApps->GetEarliestPurchaseUnixTime(appID); }
void Hookey_SteamApps_Class::InstallDLC(AppId_t appID) { real_steamApps->InstallDLC(appID); }
void Hookey_SteamApps_Class::UninstallDLC(AppId_t appID) { real_steamApps->UninstallDLC(appID); }
void Hookey_SteamApps_Class::RequestAppProofOfPurchaseKey(AppId_t appID) { real_steamApps->RequestAppProofOfPurchaseKey(appID); }
bool Hookey_SteamApps_Class::GetCurrentBetaName(char* pchName, int cchNameBufferSize) { return real_steamApps->GetCurrentBetaName(pchName, cchNameBufferSize); }
bool Hookey_SteamApps_Class::MarkContentCorrupt(bool bMissingFilesOnly) { return real_steamApps->MarkContentCorrupt(bMissingFilesOnly); }

uint32 Hookey_SteamApps_Class::GetInstalledDepots(AppId_t appID, DepotId_t* pvecDepots, uint32 cMaxDepots) { return real_steamApps->GetInstalledDepots(appID, pvecDepots, cMaxDepots); }
uint32 Hookey_SteamApps_Class::GetAppInstallDir(AppId_t appID, char* pchFolder, uint32 cchFolderBufferSize) { return real_steamApps->GetAppInstallDir(appID, pchFolder, cchFolderBufferSize); }
const char* Hookey_SteamApps_Class::GetLaunchQueryParam(const char* pchKey) { return real_steamApps->GetLaunchQueryParam(pchKey); }
bool Hookey_SteamApps_Class::GetDlcDownloadProgress(AppId_t nAppID, uint64* punBytesDownloaded, uint64* punBytesTotal) { return real_steamApps->GetDlcDownloadProgress(nAppID, punBytesDownloaded, punBytesTotal); }
STEAM_CALL_RESULT(FileDetailsResult_t)
SteamAPICall_t Hookey_SteamApps_Class::GetFileDetails(const char* pszFileName) { return real_steamApps->GetFileDetails(pszFileName); }
int Hookey_SteamApps_Class::GetLaunchCommandLine(char* pszCommandLine, int cubCommandLine) { return real_steamApps->GetLaunchCommandLine(pszCommandLine, cubCommandLine); }

static std::map<ISteamApps*, Hookey_SteamApps_Class> hookey_steamApps;
ISteamApps* Hookey_SteamApps() {
    typedef ISteamApps* (*Hookey_SteamApps_func)();

    ISteamApps* real_steamApps = ((Hookey_SteamApps_func)subhook_get_trampoline(SteamApps_hook))();
    auto hooky = hookey_steamApps.find(real_steamApps);

    if (hooky == std::end(hookey_steamApps)) {
        Hookey_SteamApps_Class nhooky;
        nhooky.real_steamApps = real_steamApps;
        hookey_steamApps.insert(std::make_pair(real_steamApps, nhooky));
        return Hookey_SteamApps();
    } else {
        return (ISteamApps*)&hooky->second;
    }
}

void WipeSteamApps() {
    hookey_steamApps.clear();
}

void PopulateDlc() {
    static bool poped = false;
    if (poped) {
        return;
    }
    poped = true;

    dlcs.push_back(std::make_pair(241360, "Europa Universalis IV: 100 Years War Unit Pack"));
    dlcs.push_back(std::make_pair(241361, "Europa Universalis IV: Horsemen of the Crescent Unit Pack"));
    dlcs.push_back(std::make_pair(241362, "Europa Universalis IV: Winged Hussars Unit Pack"));
    dlcs.push_back(std::make_pair(241363, "Europa Universalis IV: Star and Crescent DLC"));
    dlcs.push_back(std::make_pair(241364, "Europa Universalis IV: American Dream DLC "));
    dlcs.push_back(std::make_pair(241365, "Europa Universalis IV: Purple Phoenix"));
    dlcs.push_back(std::make_pair(241366, "Europa Universalis IV: National Monuments"));
    dlcs.push_back(std::make_pair(241367, "Europa Universalis IV: Conquest of Constantinople Music Pack"));
    dlcs.push_back(std::make_pair(241368, "Europa Universalis IV: National Monuments II"));
    dlcs.push_back(std::make_pair(241369, "Europa Universalis IV: Conquest of Paradise "));
    dlcs.push_back(std::make_pair(241370, "Europa Universalis IV: Conquistadors Unit pack"));
    dlcs.push_back(std::make_pair(241371, "Europa Universalis IV: Native Americans Unit Pack"));
    dlcs.push_back(std::make_pair(241372, "Europa Universalis IV: Songs of the New World"));
    dlcs.push_back(std::make_pair(241373, "Europa Universalis IV: Songs of Yuletide"));
    dlcs.push_back(std::make_pair(278710, "Europa Universalis IV: Native Americans II Unit Pack"));
    dlcs.push_back(std::make_pair(278711, "Europa Universalis IV: Colonial British and French Unit Pack"));
    dlcs.push_back(std::make_pair(278712, "Europa Universalis IV: Muslim Advisor Portraits"));
    dlcs.push_back(std::make_pair(279620, "Europa Universalis IV: Wealth of Nations "));
    dlcs.push_back(std::make_pair(279621, "Europa Universalis IV: Muslim Ships Unit Pack"));
    dlcs.push_back(std::make_pair(279622, "Europa Universalis IV: Trade Nations Unit Pack"));
    dlcs.push_back(std::make_pair(279623, "Europa Universalis IV: Res Publica "));
    dlcs.push_back(std::make_pair(295220, "Europa Universalis IV: Anthology of Alternate History"));
    dlcs.push_back(std::make_pair(295221, "Europa Universalis IV: Indian Subcontinent Unit Pack"));
    dlcs.push_back(std::make_pair(295222, "Europa Universalis IV: Indian Ships Unit Pack"));
    dlcs.push_back(std::make_pair(310030, "Europa Universalis IV: Republican Music Pack"));
    dlcs.push_back(std::make_pair(310031, "Europa Universalis IV: Art of War "));
    dlcs.push_back(std::make_pair(310032, "Europa Universalis IV: Evangelical Union Unit Pack"));
    dlcs.push_back(std::make_pair(310033, "Europa Universalis IV: Catholic League Unit Pack"));
    dlcs.push_back(std::make_pair(310034, "Europa Universalis IV: Songs of War Music Pack"));
    dlcs.push_back(std::make_pair(327830, "Europa Universalis IV: Guns, Drums and Steel Music Pack"));
    dlcs.push_back(std::make_pair(338160, "Europa Universalis IV: El Dorado "));
    dlcs.push_back(std::make_pair(338161, "Europa Universalis IV: El Dorado Content Pack"));
    dlcs.push_back(std::make_pair(338162, "Europa Universalis IV: Guns, Drums and Steel Volume 2"));
    dlcs.push_back(std::make_pair(338163, "Europa Universalis IV: Common Sense"));
    dlcs.push_back(std::make_pair(354790, "Europa Universalis IV: Women in History"));
    dlcs.push_back(std::make_pair(373150, "Europa Universalis IV: Common Sense Content Pack"));
    dlcs.push_back(std::make_pair(373370, "Europa Universalis IV: The Cossacks"));
    dlcs.push_back(std::make_pair(373380, "Europa Universalis IV: The Cossacks Content Pack"));
    dlcs.push_back(std::make_pair(373400, "Europa Universalis IV: Sounds from the community - Kairis Soundtrack"));
    dlcs.push_back(std::make_pair(414301, "Europa Universalis IV: Catholic Majors Unit Pack "));
    dlcs.push_back(std::make_pair(415680, "Europa Universalis IV: Sabaton Soundtrack"));
    dlcs.push_back(std::make_pair(436120, "Europa Universalis IV: Mare Nostrum "));
    dlcs.push_back(std::make_pair(436121, "Europa Universalis IV: Mare Nostrum Content Pack "));
    dlcs.push_back(std::make_pair(443720, "Europa Universalis IV: Kairis Soundtrack Part II"));
    dlcs.push_back(std::make_pair(472030, "Europa Universalis IV: Fredman's Epistles"));
    dlcs.push_back(std::make_pair(486970, "Europa Universalis IV: Fredman's Midsummer Epistles"));
    dlcs.push_back(std::make_pair(486570, "Europa Universalis IV: Rights of Man"));
    dlcs.push_back(std::make_pair(486571, "Europa Universalis IV: Rights of Man Content Pack"));
    dlcs.push_back(std::make_pair(487150, "Europa Universalis IV: Songs of Regency"));
    dlcs.push_back(std::make_pair(538020, "Europa Universalis IV: Mandate of Heaven"));
    dlcs.push_back(std::make_pair(538021, "Europa Universalis IV: Mandate of Heaven Content Pack"));
    dlcs.push_back(std::make_pair(539260, "Europa Universalis IV: Evangelical Majors Unit Pack"));
    dlcs.push_back(std::make_pair(625050, "Europa Universalis IV: Immersion Pack: Europa Universalis IV: Third Rome"));
    dlcs.push_back(std::make_pair(642780, "Europa Universalis IV: Music: Europa Universalis IV: The Rus Awakening"));
    dlcs.push_back(std::make_pair(721340, "Europa Universalis IV: Cradle of Civilization"));
    dlcs.push_back(std::make_pair(721341, "Europa Universalis IV: Cradle of Civilization Content Pack"));
    dlcs.push_back(std::make_pair(760070, "Europa Universalis IV: Immersion Pack: Europa Universalis IV: Rule Britannia"));
    dlcs.push_back(std::make_pair(775740, "Europa Universalis IV: Rule Britannia Music Pack"));
    dlcs.push_back(std::make_pair(827240, "Europa Universalis IV: Expansion Dharma"));
    dlcs.push_back(std::make_pair(827250, "Europa Universalis IV: Dharma Content Pack "));
    dlcs.push_back(std::make_pair(960920, "Europa Universalis IV: Immersion Pack: Europa Universalis IV: Golden Century"));
}
