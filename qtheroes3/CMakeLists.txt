cmake_minimum_required(VERSION 3.16.3)

project(qt_homm3 VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(BIN_DIR "." CACHE STRING "Where to install binaries")
set(DATA_DIR "." CACHE STRING "Where to install data files")
install(DIRECTORY config DESTINATION ${DATA_DIR})
# install(TARGETS qt_homm3 DESTINATION ${BIN_DIR})

set(client_SRCS
	../client/StdInc.cpp
	../client/../CCallback.cpp

	../client/battle/CBattleAnimations.cpp
	../client/battle/CBattleInterfaceClasses.cpp
	../client/battle/CBattleInterface.cpp
	../client/battle/CCreatureAnimation.cpp

	../client/gui/CAnimation.cpp
	../client/gui/CCursorHandler.cpp
	../client/gui/CGuiHandler.cpp
	../client/gui/CIntObject.cpp
	../client/gui/Fonts.cpp
	../client/gui/Geometries.cpp
	../client/gui/SDL_Extensions.cpp

	../client/widgets/AdventureMapClasses.cpp
	../client/widgets/Buttons.cpp
	../client/widgets/CArtifactHolder.cpp
	../client/widgets/CComponent.cpp
	../client/widgets/CGarrisonInt.cpp
	../client/widgets/Images.cpp
	../client/widgets/MiscWidgets.cpp
	../client/widgets/ObjectLists.cpp
	../client/widgets/TextControls.cpp

	../client/windows/CAdvmapInterface.cpp
	../client/windows/CCastleInterface.cpp
	../client/windows/CCreatureWindow.cpp
	../client/windows/CreaturePurchaseCard.cpp
	../client/windows/CHeroWindow.cpp
	../client/windows/CKingdomInterface.cpp
	../client/windows/CQuestLog.cpp
	../client/windows/CSpellWindow.cpp
	../client/windows/CTradeWindow.cpp
	../client/windows/CWindowObject.cpp
	../client/windows/GUIClasses.cpp
	../client/windows/InfoWindows.cpp
	../client/windows/QuickRecruitmentWindow.cpp

	../client/mainmenu/CMainMenu.cpp
	../client/mainmenu/CCampaignScreen.cpp
	../client/mainmenu/CreditsScreen.cpp
	../client/mainmenu/CPrologEpilogVideo.cpp

	../client/lobby/CBonusSelection.cpp
	../client/lobby/CSelectionBase.cpp
	../client/lobby/CLobbyScreen.cpp
	../client/lobby/CSavingScreen.cpp
	../client/lobby/CScenarioInfoScreen.cpp
	../client/lobby/OptionsTab.cpp
	../client/lobby/RandomMapTab.cpp
	../client/lobby/SelectionTab.cpp

	../client/CBitmapHandler.cpp
	../client/CreatureCostBox.cpp
	../client/CGameInfo.cpp
	../client/Client.cpp
	../client/CMessage.cpp
	../client/CMT.cpp
	../client/CMusicHandler.cpp
	../client/CPlayerInterface.cpp
	../client/CVideoHandler.cpp
	../client/CServerHandler.cpp
	../client/Graphics.cpp
	../client/mapHandler.cpp
	../client/NetPacksClient.cpp
	../client/NetPacksLobbyClient.cpp
	../client/SDLRWwrapper.cpp
)

set(client_HEADERS
	../client/StdInc.h

	../client/battle/CBattleAnimations.h
	../client/battle/CBattleInterfaceClasses.h
	../client/battle/CBattleInterface.h
	../client/battle/CCreatureAnimation.h

	../client/gui/CAnimation.h
	../client/gui/CCursorHandler.h
	../client/gui/CGuiHandler.h
	../client/gui/CIntObject.h
	../client/gui/Fonts.h
	../client/gui/Geometries.h
	../client/gui/SDL_Compat.h
	../client/gui/SDL_Extensions.h
	../client/gui/SDL_Pixels.h

	../client/widgets/AdventureMapClasses.h
	../client/widgets/Buttons.h
	../client/widgets/CArtifactHolder.h
	../client/widgets/CComponent.h
	../client/widgets/CGarrisonInt.h
	../client/widgets/Images.h
	../client/widgets/MiscWidgets.h
	../client/widgets/ObjectLists.h
	../client/widgets/TextControls.h
	../client/windows/CAdvmapInterface.h
	../client/windows/CCastleInterface.h
	../client/windows/CCreatureWindow.h
	../client/windows/CreaturePurchaseCard.h
	../client/windows/CHeroWindow.h
	../client/windows/CKingdomInterface.h
	../client/windows/CQuestLog.h
	../client/windows/CSpellWindow.h
	../client/windows/CTradeWindow.h
	../client/windows/CWindowObject.h
	../client/windows/GUIClasses.h
	../client/windows/InfoWindows.h
	../client/windows/QuickRecruitmentWindow.h

	../client/mainmenu/CMainMenu.h
	../client/mainmenu/CCampaignScreen.h
	../client/mainmenu/CreditsScreen.h
	../client/mainmenu/CPrologEpilogVideo.h

	../client/lobby/CBonusSelection.h
	../client/lobby/CSelectionBase.h
	../client/lobby/CLobbyScreen.h
	../client/lobby/CSavingScreen.h
	../client/lobby/CScenarioInfoScreen.h
	../client/lobby/OptionsTab.h
	../client/lobby/RandomMapTab.h
	../client/lobby/SelectionTab.h

	../client/CBitmapHandler.h
	../client/CreatureCostBox.h
	../client/CGameInfo.h
	../client/Client.h
	../client/CMessage.h
	../client/CMT.h
	../client/CMusicHandler.h
	../client/CPlayerInterface.h
	../client/CVideoHandler.h
	../client/CServerHandler.h
	../client/Graphics.h
	../client/mapHandler.h
	../client/resource.h
	../client/SDLMain.h
	../client/SDLRWwrapper.h
)

if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

find_package(Qt5 COMPONENTS Widgets REQUIRED)



add_executable(qt_homm3
    mainwindow.ui
    mainwindow.cpp
    main.cpp
    ${client_SRCS}
    ${client_HEADERS}
)

target_link_libraries(qt_homm3 Qt5::Widgets vcmi ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARY} ${SDL2_MIXER_LIBRARY} ${SDL2_TTF_LIBRARY} ${FFMPEG_LIBRARIES} ${FFMPEG_EXTRA_LINKING_OPTIONS})

target_include_directories(qt_homm3
	PUBLIC	${CMAKE_CURRENT_SOURCE_DIR}
	PUBLIC	${SDL2_INCLUDE_DIR}
	PRIVATE ${SDL2_TTF_INCLUDE_DIR}
	PRIVATE ${SDL2_MIXER_INCLUDE_DIR}
	PRIVATE ${SDL2_IMAGE_INCLUDE_DIR}
	PRIVATE ${FFMPEG_INCLUDE_DIRS}
    ../client
)


vcmi_set_output_dir(qt_homm3 "")
cotire(qt_homm3)
include_directories(../client)

link_directories(../client)

install(TARGETS qt_homm3 DESTINATION ${BIN_DIR})
