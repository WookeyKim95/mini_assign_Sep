#pragma once

enum class KEY
{
	UP,		// VK_UP
	DOWN,
	LEFT,
	RIGHT,

	SPACE,
	ENTER,
	ESC,
	LALT,
	LCTRL,
	LSHIFT,
	TAB,

	LBTN,
	RBTN,
	
	Q,
	W,
	E,
	R,

	A,
	S,
	D,
	F,

	END,
};

enum class KEY_STATE
{
	TAP,
	PRESSED,
	RELEASE,
	NONE,
};


struct tKeyInfo
{
	KEY			key;
	KEY_STATE	state;
	bool		bPrev;
};




class CKeyMgr
{
	SINGLE(CKeyMgr);

private:
	vector<tKeyInfo>	m_vecKey;


public:
	void init();
	void tick();


public:
	KEY_STATE GetKeyState(KEY _key)
	{
		return m_vecKey[(UINT)_key].state;
	}
};

