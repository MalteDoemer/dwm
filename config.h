/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 0;        /* border pixel of windows */
static const int startwithgaps[]    = { 1 };	/* 1 means gaps are used by default, this can be customized for each tag */
static const unsigned int gappx[]   = { 10 };   /* default gap between windows in pixels, this can be customized for each tag */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int horizpadbar        = 0;        /* horizontal padding for statusbar */
static const int vertpadbar         = 8;        /* vertical padding for statusbar */

// static const char *fonts[]          = { "Material Design Icons:size=18", "monospace:size=14" };
static const char *fonts[]          = { "FontAwesome:size=16", "monospace:size=14" };

#include "themes/basic.h"

/* color schemes */
enum { 
	SchemeNorm, 
	SchemeSel, 
	SchemeBlack,
	SchemeGrey,
	SchemeWhite,
	SchemeRed,
	SchemeOrange,
	SchemeYellow,
	SchemeGreen,
	SchemeBlue,
	SchemePink,
	SchemeWarn, 
	SchemeUrgent
}; 

static const char *colors[][3]      = {
	/*					fg         bg          border   */
	[SchemeNorm] =	 { fg_col, bg_col,  border_col },
	[SchemeSel]  =	 { fg_col_selected, bg_col_selected,   border_col },
	[SchemeBlack] = {  black, bg_col, border_col  },
	[SchemeGrey] = {  grey, bg_col, border_col  },
	[SchemeWhite] = {  white, bg_col, border_col  },
	[SchemeRed] = {  red, bg_col, border_col  },
	[SchemeOrange] = {  orange, bg_col, border_col  },
	[SchemeYellow] = {  yellow, bg_col, border_col  },
	[SchemeGreen] = {  green, bg_col, border_col  },
	[SchemeBlue] = {  blue, bg_col, border_col  },
	[SchemePink] = {  pink, bg_col, border_col  },
	[SchemeWarn] =	 { yellow, bg_col, border_col },
	[SchemeUrgent]=	 { white, red, red },
};

/* tagging */
//static const char *tags[] = { "\U000F07B7", "\U000F0239", "\U000F0A1E", "\U000F0219", "\U000F048A", "\U000F0293", "\U000F0293", "\U000F0293", "\U000F0770", "\U000F033E" };
static const char *tags[] = { "", "", "", "", "", "", "", "", "", "" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Firefox",  NULL,       NULL,       1 << 1,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod1Mask

#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { "/bin/sh", "-c", cmd, NULL }

/* commands */
static const char *dmenucmd[] = { "rofi", "-modi", "drun", "-show", "drun", "-config", "~/.config/rofi/dmenu.rasi",  NULL };
static const char *termcmd[]  = { "xfce4-terminal", NULL };
static const char *firefoxcmd[] = { "firefox", NULL  };

static const char *powermenucmd[] = { "powermenu", NULL };
static const char *powerprofilemenucmd[] = { "powerprofile", NULL };
static const char *wifimenucmd[] = { "wifimenu", NULL };
static const char *screenlayoutcmd[] = { "layoutmenu", NULL };

static const char *raisevol[] = SHCMD("amixer_wrapper set Master 5%+");
static const char *lowervol[] = SHCMD("amixer_wrapper set Master 5%-");
static const char *togglevol[] = SHCMD("amixer_wrapper set Master toggle");

static const char *brightnessup[] = SHCMD("brightnessctl_wrapper s +5%");
static const char *brightnessdown[] = SHCMD("brightnessctl_wrapper s 5%-");

static const Key keys[] = {
	/* modifier                     key        function         argument */

    /* launch apps */
	{ MODKEY,                       XK_d,      spawn,           {.v = dmenucmd } },
	{ MODKEY,                       XK_n,      spawn,           {.v = termcmd } },
    { MODKEY,                       XK_m,      spawn,           {.v = firefoxcmd } },

	{ MODKEY,                       XK_p,      spawn,           {.v = powermenucmd } },
	{ MODKEY|ShiftMask,  			XK_p,      spawn,           {.v = powerprofilemenucmd } },
	{ MODKEY,             			XK_l,      spawn,           {.v = screenlayoutcmd } },
	{ MODKEY,						XK_c,      spawn,           {.v = wifimenucmd } },


    /* control windowing layout */
	{ MODKEY,                       XK_b,      togglebar,       {0} },
	{ MODKEY,                       XK_j,      focusstack,      {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,      {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,      {.i = +1 } },
	{ MODKEY,                       XK_o,      incnmaster,      {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,        {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,        {.f = +0.05} },
	{ MODKEY,                       XK_u,      zoom,            {0} },
	{ MODKEY,                       XK_Tab,    view,            {0} },
	{ MODKEY|ShiftMask,             XK_t,      setlayout,       {.v = &layouts[0]} },
	{ MODKEY,                       XK_space,  setlayout,       {.v = &layouts[1]} },
	{ MODKEY|ShiftMask,             XK_m,      setlayout,       {.v = &layouts[2]} },

    /* control monitors */
	{ MODKEY,                       XK_comma,  focusmon,         {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,         {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,           {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,           {.i = +1 } },


    /* kill and quit  */ 
    { MODKEY,                       XK_q,      killclient,     {0} },
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
   
    /* control gaps */
	{ MODKEY,                       XK_apostrophe,      setgaps, {.i = -5 } },
	{ MODKEY,                       XK_dead_circumflex, setgaps, {.i = +5 } },
	{ MODKEY|ShiftMask,             XK_apostrophe,      setgaps, {.i = GAP_RESET } },
	{ MODKEY|ShiftMask,             XK_dead_circumflex, setgaps, {.i = GAP_TOGGLE} },

	/* multimedia keys */
	{ 0, 							XF86XK_AudioMute, 			spawn,	 {.v = togglevol      } },
	{ 0, 							XF86XK_AudioRaiseVolume, 	spawn,	 {.v = raisevol   	  } },
	{ 0, 							XF86XK_AudioLowerVolume, 	spawn,	 {.v = lowervol 	  } },
	{ 0, 							XF86XK_MonBrightnessUp, 	spawn,	 {.v = brightnessup   } },
	{ 0, 							XF86XK_MonBrightnessDown, 	spawn,	 {.v = brightnessdown } },

    /* tags */
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
    TAGKEYS(                        XK_0,                      9)
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};


