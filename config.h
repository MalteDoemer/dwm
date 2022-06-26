/* See LICENSE file for copyright and license details. */

#pragma once

#include "src/dwm.h"

/* appearance */
static const unsigned int borderpx  = 0;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "fontawesome:size=14" };
static const char dmenufont[]       = "fontawesome:size=14";

/* default gap between windows */
static const Gap default_gap        = {.isgap = 1, .realgap = 5, .gappx = 5};

/* colors */
static const char col_gray1[]       = "#333333";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_green[]       = "#155133";
static const char col_yellow[]      = "#ffff00";
static const char col_red[]         = "#ff0000";

static const char *colors[][3]      = {
    /*                   fg          bg         border   */
    [SchemeNorm]     = { col_gray3,  col_gray1, col_gray2 },
    [SchemeSel]      = { col_gray1,  col_gray3, col_gray2 },
    [SchemeTitleBar] = { col_gray1,  col_gray1, col_gray2 }, // make fg = bg to hide the text XD
    [SchemeGreenFg]  = { col_green,  col_gray1, col_gray2 },
    [SchemeYellowFg] = { col_yellow, col_gray1, col_gray2 },
    [SchemeRedFg]    = { col_red,    col_gray1, col_gray2 },
};

/* tagging */
static const char *tags[] = { "", "", "", "", "", "6",  "7", "8", "9", "" };

static const Rule rules[] = {
    /* xprop(1):
     *  WM_CLASS(STRING) = instance, class
     *  WM_NAME(STRING) = title
     */
    /* class            instance    title       tags mask   isfloating  monitor */
    { "xfce4-terminal", NULL,       NULL,       1 << 0,     0,          0 },
    { "firefox",        NULL,       NULL,       1 << 1,     0,          0 },
    { "code-oss",       NULL,       NULL,       1 << 2,     0,          0 },
    { "libreoffice",    NULL,       NULL,       1 << 3,     0,          0 },
    { "p3x-onenote",    NULL,       NULL,       1 << 3,     0,          0 },
    { "Mail",           NULL,       NULL,       1 << 4,     0,          0 },
    { "discord",        NULL,       NULL,       1 << 4,     0,          0 },
    { "keepassxc",      NULL,       NULL,       1 << 10,    0,          0 },

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
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */

static const char *dmenucmd[] = { 
    "dmenu_run", 
    "-m", dmenumon, 
    "-fn", dmenufont, 
    "-nb", col_gray1, 
    "-nf", col_gray3, 
    "-sb", col_gray3, 
    "-sf", col_gray1, 
    NULL 
};

static const char *termcmd[]  = { "xfce4-terminal", NULL };
static const char *firefoxcmd[]  = { "firefox", NULL };

static const char *brightnessup[] = { "xbacklight", "-inc", "5", NULL  };
static const char *brightnessdown[] = { "xbacklight", "-dec", "5", NULL  };

static const char *togglevol[] =  { "amixer", "sset", "Master", "toggle", NULL  };
static const char *raisevol[] = { "amixer", "sset", "Master", "5%+", NULL  };
static const char *lowervol[] = { "amixer", "sset", "Master", "5%-", NULL  };

static const char *shutdowncmd[] = {"systemctl", "poweroff", NULL};
static const char *rebootcmd[] = {"systemctl", "reboot", NULL};
static const char *suspendcmd[] = {"systemctl", "suspend", NULL};
static const char *hibernatecmd[] = {"systemctl", "hibernate", NULL};
static const char *lockcmd[] = {"dm-tool", "lock", NULL};

static const RofiMenuEntry powermenu_entries[] = {
    { .name = " Shutdown", .argv =  shutdowncmd },
    { .name = " Reboot", .argv = rebootcmd },
    { .name = " Suspend", .argv = suspendcmd },
    { .name = " Hibernate", .argv = hibernatecmd },
    { .name = " Lock", .argv = lockcmd },
    { .name = " Cancle", .argv = NULL },
};

static const RofiMenu powermenu = {
    .fg_color = "#bbbbbb",
    .bg_color = "#111111",
    .hlfg_color = "#bbbbbb",
    .hlbg_color = "#111111",
    .border_color = "#222222",
    .config_file = "~/.config/dwm/rofi/powermenu.rasi",
    .prompt = "",
    .entry_count = LENGTH(powermenu_entries),
    .menu_entries = powermenu_entries
};

static const char *performancecmd[] = {"powerprofilesctl", "set", "performance", NULL};
static const char *balancedcmd[] = {"powerprofilesctl", "set", "balanced", NULL};
static const char *powersavercmd[] = {"powerprofilesctl", "set", "power-saver", NULL};

static const RofiMenuEntry powerprofile_entries[] = {
    { .name = " Performance", .argv =  performancecmd },
    { .name = " Balanced", .argv = balancedcmd },
    { .name = " Power Saver", .argv = powersavercmd },
    { .name = " Cancle", .argv = NULL },
};

static const RofiMenu powerprofile_menu = {
    .fg_color = "#bbbbbb",
    .bg_color = "#111111",
    .hlfg_color = "#bbbbbb",
    .hlbg_color = "#111111",
    .border_color = "#222222",
    .config_file = "~/.config/dwm/rofi/powerprofile.rasi",
    .prompt = "",
    .entry_count = LENGTH(powerprofile_entries),
    .menu_entries = powerprofile_entries
};

static Key keys[] = {
    /* modifier                     key        function        argument */

    /* launch apps */
    { MODKEY,                       XK_d,      spawn,          {.v = dmenucmd } },
    { MODKEY,                       XK_n,      spawn,          {.v = termcmd } },
    { MODKEY,                       XK_m,      spawn,          {.v = firefoxcmd } },

    /* control windowing layout */
    { MODKEY,                       XK_b,      togglebar,      {0} },
    { MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
    { MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
    { MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
    { MODKEY,                       XK_o,      incnmaster,     {.i = -1 } },
    { MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
    { MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
    { MODKEY,                       XK_u,      zoom,           {0} },
    { MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,                       XK_space,  setlayout,      {.v = &layouts[1]} },
	{ MODKEY|ShiftMask,             XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY|ShiftMask,             XK_m,      setlayout,      {.v = &layouts[2]} },

    /* control monitors */
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },

    /* special keys */
	{ 0, XF86XK_MonBrightnessUp,                spawn,		   {.v = brightnessup } },
	{ 0, XF86XK_MonBrightnessDown,              spawn,		   {.v = brightnessdown } },
	{ 0, XF86XK_AudioRaiseVolume,               spawn,		   {.v = raisevol } },
	{ 0, XF86XK_AudioLowerVolume,               spawn,		   {.v = lowervol } },
	{ 0, XF86XK_AudioMute,                      spawn,		   {.v = togglevol } },

    /* menus */
    { MODKEY,                       XK_p,       rofimenu,      {.v = &powermenu} },
    { MODKEY|ShiftMask,             XK_p,       rofimenu,      {.v = &powerprofile_menu} },
	
    /* tags */
    { MODKEY,                       XK_a, shiftview, {.i = -1 } },
	{ MODKEY,                       XK_s, shiftview, {.i = +1 } },

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

    { MODKEY,                       XK_q,      killclient,     {0} },
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },

	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

