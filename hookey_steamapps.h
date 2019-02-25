#ifndef HOOKEY_STEAMAPPS_H
#define HOOKEY_STEAMAPPS_H

#include "hookey_common.h"

class Hookey_SteamApps_Class : public ISteamApps {
    public:
	bool BIsSubscribed();
	bool BIsLowViolence();
	bool BIsCybercafe();
	bool BIsVACBanned();
	int GetDLCCount();
	bool BIsDlcInstalled(AppId_t appID);
	bool BGetDLCDataByIndex(int iDLC, AppId_t *pAppID, bool *pbAvailable, char *pchName, int cchNameBufferSize);

	const char *GetCurrentGameLanguage();
	const char *GetAvailableGameLanguages();
	bool BIsSubscribedApp( AppId_t appID );
	uint32 GetEarliestPurchaseUnixTime( AppId_t nAppID );
	bool BIsSubscribedFromFreeWeekend();
	void InstallDLC( AppId_t nAppID );
	void UninstallDLC( AppId_t nAppID );
	void RequestAppProofOfPurchaseKey( AppId_t nAppID );
	bool GetCurrentBetaName( char *pchName, int cchNameBufferSize );
	bool MarkContentCorrupt( bool bMissingFilesOnly );
	uint32 GetInstalledDepots( AppId_t appID, DepotId_t *pvecDepots, uint32 cMaxDepots );
	uint32 GetAppInstallDir( AppId_t appID, char *pchFolder, uint32 cchFolderBufferSize );
	bool BIsAppInstalled( AppId_t appID );
	CSteamID GetAppOwner();
	const char *GetLaunchQueryParam( const char *pchKey );
	bool GetDlcDownloadProgress( AppId_t nAppID, uint64 *punBytesDownloaded, uint64 *punBytesTotal );
	int GetAppBuildId();
	void RequestAllProofOfPurchaseKeys();
	STEAM_CALL_RESULT( FileDetailsResult_t )
	SteamAPICall_t GetFileDetails( const char* pszFileName );
	int GetLaunchCommandLine( char *pszCommandLine, int cubCommandLine );
	bool BIsSubscribedFromFamilySharing();

    ISteamApps* real_steamApps;
};

ISteamApps* Hookey_SteamApps();
void PopulateDlc();
void WipeSteamApps();

#endif
