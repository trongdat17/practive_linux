        LC_ST_UPGRADE_RES stUpgradeResLCTool;             // status upgrade execute file to LCTOOL
        CHAR  szExecFile[MAX_PATH] = "";                  // path of execute file Upgrade
        INT   iPid = -1;                                  // return of fork()
        INT   iRet = -1;                                  // check return of function  
        INT   iSocket = 0;                                // Socket
        CHAR  cSocket[100] = {0x00};                      // socket with char data

        // Get path execute file Upgrade process
        sprintf(szExecFile, "%s%s", APL_DIR_PATH, UPGRADE_EXECUTE_FILE);
        if(lpstEvt != NULL)
        {
            // Get socket from Communication thread
            iSocket = *(INT*)lpstEvt->byMsgBuf;
            if (stUpgradeRes.byUpgradeSituation == LC_UPGRADE_START)
            {
                iPid = fork();
    
                if (iPid == -1) // Error
                {
                    stUpgradeRes.byUpgradeSituation = LC_UPGRADE_SUSPEN;
                }
                else if (iPid == 0) // Child Process
                {
                    // Child Process
                    sprintf(cSocket,"%d",iSocket);
                    iRet = execl(szExecFile,cSocket,NULL);
                    if(iRet == -1)
                    {
                        stUpgradeRes.byUpgradeSituation = LC_UPGRADE_SUSPEN;
                    }
        
                }
                else  // Current Process
                {
        
                }
            }
    
            // Send message to communication thread
            stUpgradeResLCTool.uiKindOfRes = LCTOOL_LC_UPGRADE_RES;
            stUpgradeResLCTool.stUpgrade = stUpgradeRes;
            lpLibPM->SndMessage(PROC_LC_COM,
                               COM_SENDRES,
                               (LPBYTE)&stUpgradeResLCTool,
                                sizeof(stUpgradeResLCTool));
        }
        
        
        
        
        
            LibPM<LCUpgrade::Upgrade>       libPM;                      // LibPM object
    LCUpgrade::Upgrade              upgradeMain(&libPM);        // Create Main thread object
    LIBERRINFO                      stLibErrInfo;               // Library Error info
    STATUS                          iRet;                       // Function return value
    UINT                            uiCnt;                      // Count Index
    INT                             iArgIdx;                    // Argurment index
    try
    {
        // socket = LCStringToNumber(string(argv[1]), 10);
        upgradeMain.socket = atoi(iArgv[0]);

        // Get file names from arguments
        for( iArgIdx = 2; iArgIdx < iArgc; iArgIdx++)
        {
            LCUpgrade::Upgrade::listUpgradeFileNames.push_back(iArgv[iArgIdx]);
        }
    }
    
    
    
    #define SEM_INIT_VAL        (1)
#define SEM_EVT_COM         "lc_evtComStop"
#define SEM_EVT_LOG_COM     "lc_evtLogColStop"
#define SEM_EVT_FLUSH_LOG   "lc_evtFlushEventLog"
    #define SEM_PERMS           (S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP)
    evtFlushEventLog = sem_open(SEM_EVT_FLUSH_LOG, O_CREAT, SEM_PERMS, SEM_INIT_VAL);
