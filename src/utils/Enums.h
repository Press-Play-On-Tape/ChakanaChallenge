#pragma once

enum class MusicSong : uint8_t {
    MainTheme
};

enum class MusicSFX : uint8_t {
    SFX_Death,
    SFX_Victory,
    SFX_XPGain,
    SFX_Three_Inc,
    SFX_Three_Dec,
    SFX_PlayerBlip,
    SFX_EnemyBlip,
    SFX_Explosion,
    SFX_DoubleBeep,
    SFX_DoubleBeepDown,
    SFX_Bet1,
    SFX_Bet2,
    SFX_Bet3,
    SFX_Bet4,
    SFX_Bet5,
    SFX_Bet6,
    SFX_Click,
    SFX_SmallBlind,
    SFX_BigBlind,
};


enum class Direction : uint8_t {
    Backward,
    Right,
    Forward,
    Left,
};


enum Stance : uint16_t {

    Man_Start,

        Man_BK_Start = Man_Start,

            Man_Walk_BK_01 = Man_BK_Start,
            Man_Walk_BK_02,
            Man_Walk_BK_03,
            Man_Walk_BK_04,
            
            Man_StandingJump_BK_01,
            Man_StandingJump_BK_02,
            Man_StandingJump_BK_03,
            Man_StandingJump_BK_04,
            Man_StandingJump_BK_05,
            Man_StandingJump_BK_06,
            Man_StandingJump_BK_07,

            Man_StandingJump_BK_UP_01,     // Jump Up
            Man_StandingJump_BK_UP_02,
            Man_StandingJump_BK_UP_03,
            Man_StandingJump_BK_UP_04,
            Man_StandingJump_BK_UP_05,
            Man_StandingJump_BK_UP_06,

            Man_ClimbLadder_BK_RH_UP_01,
            Man_ClimbLadder_BK_RH_UP_02,
            Man_ClimbLadder_BK_RH_UP_03,
            Man_ClimbLadder_BK_RH_UP_04,
            Man_ClimbLadder_BK_RH_UP_05,
            Man_ClimbLadder_BK_RH_UP_06,
            Man_ClimbLadder_BK_RH_UP_07,
            Man_ClimbLadder_BK_RH_UP_08,
            Man_ClimbLadder_BK_RH_UP_09,
            Man_ClimbLadder_BK_RH_UP_10,
            Man_ClimbLadder_BK_RH_UP_11,
            Man_ClimbLadder_BK_RH_UP_12,
            Man_ClimbLadder_BK_RH_UP_13,
            Man_ClimbLadder_BK_RH_UP_14,

            Man_ClimbLadder_BK_RH_DOWN_01,
            Man_ClimbLadder_BK_RH_DOWN_02,
            Man_ClimbLadder_BK_RH_DOWN_03,
            Man_ClimbLadder_BK_RH_DOWN_04,
            Man_ClimbLadder_BK_RH_DOWN_05,
            Man_ClimbLadder_BK_RH_DOWN_06,
            Man_ClimbLadder_BK_RH_DOWN_07,
            Man_ClimbLadder_BK_RH_DOWN_08,
            Man_ClimbLadder_BK_RH_DOWN_09,
            Man_ClimbLadder_BK_RH_DOWN_10,
            Man_ClimbLadder_BK_RH_DOWN_11,
            Man_ClimbLadder_BK_RH_DOWN_12,
            Man_ClimbLadder_BK_RH_DOWN_13,
            Man_ClimbLadder_BK_RH_DOWN_14,

            Man_ClimbLadder_BK_LH_UP_01,
            Man_ClimbLadder_BK_LH_UP_02,
            Man_ClimbLadder_BK_LH_UP_03,
            Man_ClimbLadder_BK_LH_UP_04,
            Man_ClimbLadder_BK_LH_UP_05,
            Man_ClimbLadder_BK_LH_UP_06,
            Man_ClimbLadder_BK_LH_UP_07,
            Man_ClimbLadder_BK_LH_UP_08,
            Man_ClimbLadder_BK_LH_UP_09,
            Man_ClimbLadder_BK_LH_UP_10,
            Man_ClimbLadder_BK_LH_UP_11,
            Man_ClimbLadder_BK_LH_UP_12,
            Man_ClimbLadder_BK_LH_UP_13,
            Man_ClimbLadder_BK_LH_UP_14,

            Man_ClimbLadder_BK_LH_DOWN_01,
            Man_ClimbLadder_BK_LH_DOWN_02,
            Man_ClimbLadder_BK_LH_DOWN_03,
            Man_ClimbLadder_BK_LH_DOWN_04,
            Man_ClimbLadder_BK_LH_DOWN_05,
            Man_ClimbLadder_BK_LH_DOWN_06,
            Man_ClimbLadder_BK_LH_DOWN_07,
            Man_ClimbLadder_BK_LH_DOWN_08,
            Man_ClimbLadder_BK_LH_DOWN_09,
            Man_ClimbLadder_BK_LH_DOWN_10,
            Man_ClimbLadder_BK_LH_DOWN_11,
            Man_ClimbLadder_BK_LH_DOWN_12,
            Man_ClimbLadder_BK_LH_DOWN_13,
            Man_ClimbLadder_BK_LH_DOWN_14,

        Man_BK_End = Man_ClimbLadder_BK_LH_DOWN_14,
        
        Man_RH_Start,

            Man_Walk_RH_00 = Man_RH_Start,                 // No movement
            Man_Walk_RH_01,
            Man_Walk_RH_02,
            Man_Walk_RH_03,
            Man_Walk_RH_04,

            Man_ClimbStairs_RH_01,
            Man_ClimbStairs_RH_02,
            Man_ClimbStairs_RH_03,
            Man_ClimbStairs_RH_04,
            Man_ClimbStairs_RH_05,
            Man_ClimbStairs_RH_06,
            Man_ClimbStairs_RH_07,
            Man_ClimbStairs_RH_08,

            Man_DescendStairs_RH_01,
            Man_DescendStairs_RH_02,
            Man_DescendStairs_RH_03,
            Man_DescendStairs_RH_04,
            Man_DescendStairs_RH_05,
            Man_DescendStairs_RH_06,
            Man_DescendStairs_RH_07,
            Man_DescendStairs_RH_08,

            Man_Walk_FallDown_RH_01,
            Man_Walk_FallDown_RH_02,
            Man_Walk_FallDown_RH_03,
            Man_Walk_FallDown_RH_04,
            Man_Walk_FallDown_RH_05,
            Man_Walk_FallDown_RH_06,

            Man_Walk_FallMore_RH_01,
            Man_Walk_FallMore_RH_02,

            Man_Walk_FallLand_RH_01,
            Man_Walk_FallLand_RH_02,
            Man_Walk_FallLand_RH_03,
            Man_Walk_FallLand_RH_04,

            Man_StandingJump_RH_01,
            Man_StandingJump_RH_02,
            Man_StandingJump_RH_03,
            Man_StandingJump_RH_04,
            Man_StandingJump_RH_05,
            Man_StandingJump_RH_06,
            Man_StandingJump_RH_07,
            
            Man_StandingJump_Small_RH_01,
            Man_StandingJump_Small_RH_02,
            Man_StandingJump_Small_RH_03,

            Man_StandingJump_RH_UP_01,     // Jump Up
            Man_StandingJump_RH_UP_02,
            Man_StandingJump_RH_UP_03,
            Man_StandingJump_RH_UP_04,
            Man_StandingJump_RH_UP_05,
            Man_StandingJump_RH_UP_06,
                    
            Man_StandingJump_RH_UPandOver_01,     // Jump Up
            Man_StandingJump_RH_UPandOver_02,
            Man_StandingJump_RH_UPandOver_03,
            Man_StandingJump_RH_UPandOver_04,
            Man_StandingJump_RH_UPandOver_05,
            Man_StandingJump_RH_UPandOver_06,
            
            Man_WalkingJump_RH_01,
            Man_WalkingJump_RH_02,
            Man_WalkingJump_RH_03,
            Man_WalkingJump_RH_04,
            Man_WalkingJump_RH_05,
            Man_WalkingJump_RH_06,
            Man_WalkingJump_RH_07,
            Man_WalkingJump_RH_08,

            Man_WalkingJump_RH_2_01,
            Man_WalkingJump_RH_2_02,
            Man_WalkingJump_RH_2_03,
            Man_WalkingJump_RH_2_04,
            Man_WalkingJump_RH_2_05,
            Man_WalkingJump_RH_2_06,
            Man_WalkingJump_RH_2_07,
            Man_WalkingJump_RH_2_08,

            Man_WalkingJump_RH_25_01,
            Man_WalkingJump_RH_25_02,
            Man_WalkingJump_RH_25_03,
            Man_WalkingJump_RH_25_04,
            Man_WalkingJump_RH_25_05,
            Man_WalkingJump_RH_25_06,
            Man_WalkingJump_RH_25_07,
            Man_WalkingJump_RH_25_08,
            Man_WalkingJump_RH_25_09,
            Man_WalkingJump_RH_25_10,
            Man_WalkingJump_RH_25_11,

            Man_WalkingJump_RH_1D_25_01,
            Man_WalkingJump_RH_1D_25_02,
            Man_WalkingJump_RH_1D_25_03,
            Man_WalkingJump_RH_1D_25_04,
            Man_WalkingJump_RH_1D_25_05,
            Man_WalkingJump_RH_1D_25_06,
            Man_WalkingJump_RH_1D_25_07,
            Man_WalkingJump_RH_1D_25_08,
            Man_WalkingJump_RH_1D_25_09,
            Man_WalkingJump_RH_1D_25_10,
            Man_WalkingJump_RH_1D_25_11,
            
            Man_WalkingJump_RH_UP_01,
            Man_WalkingJump_RH_UP_02,
            Man_WalkingJump_RH_UP_03,
            Man_WalkingJump_RH_UP_04,
            Man_WalkingJump_RH_UP_05,
            
            Man_Rope_Start_RH_01,
            Man_Rope_Start_RH_02,
            Man_Rope_Start_RH_03,
            Man_Rope_Start_RH_04,
            Man_Rope_Start_RH_05,
            Man_Rope_Start_RH_06,
            Man_Rope_Start_RH_07,
            
            Man_Rope_End_RH_01,
            Man_Rope_End_RH_02,
            Man_Rope_End_RH_03,
            Man_Rope_End_RH_04,
            Man_Rope_End_RH_05,
            Man_Rope_End_RH_06,

            Man_Die_RH_01,
            Man_Die_RH_02,
            Man_Die_RH_03,
            Man_Die_RH_04,

        Man_RH_End = Man_Die_RH_04,
        
        Man_FW_Start,
            
            Man_Walk_FW_01 = Man_FW_Start,
            Man_Walk_FW_02,
            Man_Walk_FW_03,
            Man_Walk_FW_04,

            Man_StandingJump_FW_01,
            Man_StandingJump_FW_02,
            Man_StandingJump_FW_03,
            Man_StandingJump_FW_04,
            Man_StandingJump_FW_05,
            Man_StandingJump_FW_06,
            Man_StandingJump_FW_07,

            Man_StandingJump_FW_UP_01,     // Jump Up
            Man_StandingJump_FW_UP_02,
            Man_StandingJump_FW_UP_03,
            Man_StandingJump_FW_UP_04,
            Man_StandingJump_FW_UP_05,
            Man_StandingJump_FW_UP_06,

        Man_FW_End = Man_StandingJump_FW_UP_06,
        
        Man_LH_Start,
                
            Man_Walk_LH_00 = Man_LH_Start,                 // No movement
            Man_Walk_LH_01,
            Man_Walk_LH_02,
            Man_Walk_LH_03,
            Man_Walk_LH_04,

            Man_ClimbStairs_LH_01,
            Man_ClimbStairs_LH_02,
            Man_ClimbStairs_LH_03,
            Man_ClimbStairs_LH_04,
            Man_ClimbStairs_LH_05,
            Man_ClimbStairs_LH_06,
            Man_ClimbStairs_LH_07,
            Man_ClimbStairs_LH_08,

            Man_DescendStairs_LH_01,
            Man_DescendStairs_LH_02,
            Man_DescendStairs_LH_03,
            Man_DescendStairs_LH_04,
            Man_DescendStairs_LH_05,
            Man_DescendStairs_LH_06,
            Man_DescendStairs_LH_07,
            Man_DescendStairs_LH_08,

            Man_Walk_FallDown_LH_01,
            Man_Walk_FallDown_LH_02,
            Man_Walk_FallDown_LH_03,
            Man_Walk_FallDown_LH_04,
            Man_Walk_FallDown_LH_05,
            Man_Walk_FallDown_LH_06,

            Man_Walk_FallMore_LH_01,
            Man_Walk_FallMore_LH_02,

            Man_Walk_FallLand_LH_01,
            Man_Walk_FallLand_LH_02,
            Man_Walk_FallLand_LH_03,
            Man_Walk_FallLand_LH_04,

            Man_StandingJump_LH_01,
            Man_StandingJump_LH_02,
            Man_StandingJump_LH_03,
            Man_StandingJump_LH_04,
            Man_StandingJump_LH_05,
            Man_StandingJump_LH_06,
            Man_StandingJump_LH_07,

            Man_StandingJump_Small_LH_01,
            Man_StandingJump_Small_LH_02,
            Man_StandingJump_Small_LH_03,
                    
            Man_StandingJump_LH_UP_01,     // Jump Up
            Man_StandingJump_LH_UP_02,
            Man_StandingJump_LH_UP_03,
            Man_StandingJump_LH_UP_04,
            Man_StandingJump_LH_UP_05,
            Man_StandingJump_LH_UP_06,
                    
            Man_StandingJump_LH_UPandOver_01,     // Jump Up
            Man_StandingJump_LH_UPandOver_02,
            Man_StandingJump_LH_UPandOver_03,
            Man_StandingJump_LH_UPandOver_04,
            Man_StandingJump_LH_UPandOver_05,
            Man_StandingJump_LH_UPandOver_06,

            Man_WalkingJump_LH_01,
            Man_WalkingJump_LH_02,
            Man_WalkingJump_LH_03,
            Man_WalkingJump_LH_04,
            Man_WalkingJump_LH_05,
            Man_WalkingJump_LH_06,
            Man_WalkingJump_LH_07,
            Man_WalkingJump_LH_08,

            Man_WalkingJump_LH_2_01,
            Man_WalkingJump_LH_2_02,
            Man_WalkingJump_LH_2_03,
            Man_WalkingJump_LH_2_04,
            Man_WalkingJump_LH_2_05,
            Man_WalkingJump_LH_2_06,
            Man_WalkingJump_LH_2_07,
            Man_WalkingJump_LH_2_08,
            
            Man_WalkingJump_LH_25_01,
            Man_WalkingJump_LH_25_02,
            Man_WalkingJump_LH_25_03,
            Man_WalkingJump_LH_25_04,
            Man_WalkingJump_LH_25_05,
            Man_WalkingJump_LH_25_06,
            Man_WalkingJump_LH_25_07,
            Man_WalkingJump_LH_25_08,
            Man_WalkingJump_LH_25_09,
            Man_WalkingJump_LH_25_10,
            Man_WalkingJump_LH_25_11,
            
            Man_WalkingJump_LH_1D_25_01,
            Man_WalkingJump_LH_1D_25_02,
            Man_WalkingJump_LH_1D_25_03,
            Man_WalkingJump_LH_1D_25_04,
            Man_WalkingJump_LH_1D_25_05,
            Man_WalkingJump_LH_1D_25_06,
            Man_WalkingJump_LH_1D_25_07,
            Man_WalkingJump_LH_1D_25_08,
            Man_WalkingJump_LH_1D_25_09,
            Man_WalkingJump_LH_1D_25_10,
            Man_WalkingJump_LH_1D_25_11,
            
            Man_WalkingJump_LH_UP_01,
            Man_WalkingJump_LH_UP_02,
            Man_WalkingJump_LH_UP_03,
            Man_WalkingJump_LH_UP_04,
            Man_WalkingJump_LH_UP_05,

            Man_Rope_Start_LH_01,
            Man_Rope_Start_LH_02,
            Man_Rope_Start_LH_03,
            Man_Rope_Start_LH_04,
            Man_Rope_Start_LH_05,
            Man_Rope_Start_LH_06,
            Man_Rope_Start_LH_07,
            
            Man_Rope_End_LH_01,
            Man_Rope_End_LH_02,
            Man_Rope_End_LH_03,
            Man_Rope_End_LH_04,
            Man_Rope_End_LH_05,
            Man_Rope_End_LH_06,

            Man_Die_LH_01,
            Man_Die_LH_02,
            Man_Die_LH_03,
            Man_Die_LH_04,

        Man_LH_End = Man_Die_LH_04,
    
        Man_StandingJumpDown_RH_01,
        Man_StandingJumpDown_RH_02,
        Man_StandingJumpDown_RH_03,
        Man_StandingJumpDown_RH_04,
        Man_StandingJumpDown_RH_05,
        Man_StandingJumpDown_RH_06,
        Man_StandingJumpDown_RH_07,
        Man_StandingJumpDown_RH_08,
        Man_StandingJumpDown_RH_09,

    Man_End = Man_LH_End,
    None = 255,
};

inline Stance &operator++(Stance &c) {
  c = static_cast<Stance>( static_cast<uint8_t>(c) + 1 );
  return c;
}

inline Stance operator++(Stance &c, int) {
  Stance result = c;
  ++c;
  return result;
}


enum class GameState : uint8_t {

    SplashScreen_Start,
        SplashScreen_00 = SplashScreen_Start,
        SplashScreen_01,
        SplashScreen_02,
        SplashScreen_03,
    SplashScreen_End,

    Title_Init,
    Title_Start,
        Title_OptPlay = Title_Start,
        Title_OptSound,
        Title_OptCredits,
        Title_OptResume,
        Title_OptPlay2,
        Title_OptSound2,
        Title_OptSound_Music,
        Title_OptSound_SFX,
        Title_OptSound_Volume,
        Title_OptSound_Music2,
        Title_OptSound_SFX2,
        Title_OptSound_Volume2,
        Title_ShowCredits,
    Title_End,

    Play_Init,
    Play_Start,
        Play_BoatEnters,
        Play_PlayerJumps,
        Play_PlayerCenters,
        Play,
    Play_End,
    PlayGame_Init,
    PlayGame_Start,
        PlayGame,
    PlayGame_End,
    Map_Init,
    Map,
    Map_ShowDialogue,
    Map_MoveBoat,
};

inline GameState &operator++(GameState &c) {
  c = static_cast<GameState>( static_cast<uint8_t>(c) + 1 );
  return c;
}

inline GameState operator++(GameState &c, int) {
  GameState result = c;
  ++c;
  return result;
}
