#ifndef _ENUMERATION
#define _ENUMERATION

enum ButtonState {
	BUTTON_MOUSE_OUT,       // 0 
	BUTTON_MOUSE_HOVER,     // 1
    BUTTON_MOUSELEFT_DOWN,  // 2
    BUTTON_MOUSERIGHT_DOWN, // 3
    BUTTON_MOUSELEFT_UP,    // 4
    BUTTON_MOUSERIGHT_UP    // 5
};

enum FadeState {
    FADE_IN, FADE_OUT, STATIC
};

enum GameState {
    MAIN_MENU, PLAY, WIN, LOSE
};

enum MinefieldState {
    playing, win, lose
};

enum TileState {
    num0, num1, num2, num3, num4, num5, num6, num7, num8, bomb, flag, hidden
};

enum Level {
    easy, hard, expert, unknown
};

#endif