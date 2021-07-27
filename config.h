/* See LICENSE file for copyright and license details. */

/* appearance */
static const char font[]        = "JetBrains Mono:size=9";
static const char* normbgcolor  = "#2e3440";
static const char* normfgcolor  = "#d8dee9";
static const char* selbgcolor   = "#e0af68";
static const char* selfgcolor   = "#414868";
static const char* urgbgcolor   = "#111111";
static const char* urgfgcolor   = "#f7768e";
static const char before[]      = "<";
static const char after[]       = ">";
static const char titletrim[]   = "...";
static const int  tabwidth      = 200;
static const Bool foreground    = True;
static       Bool urgentswitch  = False;

/*
 * Where to place a new tab when it is opened. When npisrelative is True,
 * then the current position is changed + newposition. If npisrelative
 * is False, then newposition is an absolute position.
 */
static int  newposition   = 0;
static Bool npisrelative  = False;

#define SETPROP(p) { \
        .v = (char *[]){ "/bin/sh", "-c", \
                "prop=\"`xwininfo -children -id $1 | grep '^     0x' |" \
                "sed -e's@^ *\\(0x[0-9a-f]*\\) \"\\([^\"]*\\)\".*@\\1 \\2@' |" \
                "xargs -0 printf %b | dmenu -l 10 -w $1`\" &&" \
                "xprop -id $1 -f $0 8s -set $0 \"$prop\"", \
                p, winid, NULL \
        } \
}

/* Keybinding anything to CONTROL+SHIFT should be avoided. */
/* CONTROL+SHIFT is used extensively in the surf browser. */
/* Use CONTROL+ALT instead! */

#define MODKEY ControlMask
static Key keys[] = {
	/* modifier             key        function     argument */
	{ MODKEY|Mod1Mask,      XK_Return, focusonce,   { 0 } },
	{ MODKEY|Mod1Mask,      XK_Return, spawn,       { 0 } },

	{ MODKEY|Mod1Mask,      XK_l,      rotate,      { .i = +1 } },
	{ MODKEY|Mod1Mask,      XK_h,      rotate,      { .i = -1 } },
	{ MODKEY|Mod1Mask,      XK_j,      movetab,     { .i = -1 } },
	{ MODKEY|Mod1Mask,      XK_k,      movetab,     { .i = +1 } },
	{ MODKEY,               XK_Tab,    rotate,      { .i = 0 } },

	{ MODKEY,               XK_grave,  spawn,       SETPROP("_TABBED_SELECT_TAB") },
	{ MODKEY,               XK_1,      move,        { .i = 0 } },
	{ MODKEY,               XK_2,      move,        { .i = 1 } },
	{ MODKEY,               XK_3,      move,        { .i = 2 } },
	{ MODKEY,               XK_4,      move,        { .i = 3 } },
	{ MODKEY,               XK_5,      move,        { .i = 4 } },
	{ MODKEY,               XK_6,      move,        { .i = 5 } },
	{ MODKEY,               XK_7,      move,        { .i = 6 } },
	{ MODKEY,               XK_8,      move,        { .i = 7 } },
	{ MODKEY,               XK_9,      move,        { .i = 8 } },
	{ MODKEY,               XK_0,      move,        { .i = 9 } },

	{ MODKEY|Mod1Mask,      XK_q,      killclient,  { 0 } },

	{ MODKEY,               XK_u,      focusurgent, { 0 } },
	{ MODKEY|Mod1Mask,      XK_u,      toggle,      { .v = (void*) &urgentswitch } },

	{ 0,                    XK_F11,    fullscreen,  { 0 } },

	{ MODKEY,               XK_Alt_L,     showbar,    { .i = 1 } },
	{ Mod1Mask,             XK_Control_L, showbar,  { .i = 1 } },
	{ MODKEY,               XK_period,    showbar,     { .i = 1 } },
	{ MODKEY,               XK_comma,     showbar,      { .i = 0 } },
};

static Key keyreleases[] = {
	/* modifier             key           function  argument */
	{ MODKEY|Mod1Mask,      XK_Alt_L,     showbar,  { .i = 0 } },
	{ MODKEY|Mod1Mask,      XK_Control_L, showbar,  { .i = 0 } },
};
