
#include "xchat-plugin.h"

#define PNAME "AutoOp"
#define PDESC "Auto Ops anyone that joins"
#define PVERSION "0.1"

static xchat_plugin *ph;   /* plugin handle */
static int enable = 1;

static int join_cb(char *word[], void *userdata)
{
		if (enable)
				/* Op ANYONE who joins */
				xchat_commandf(ph, "OP %s", word[1]);
		/* word[1] is the nickname, as in the Settings->Advanced->TextEvents window in xchat */

		return XCHAT_EAT_NONE;  /* don't eat this event, xchat needs to see it! */
}

static int autooptoggle_cb(char *word[], char *word_eol[], void *userdata)
{
		if (!enable)
		{
				enable = 1;
				xchat_print(ph, "AutoOping now enabled!\n");
		} else
		{
				enable = 0;
				xchat_print(ph, "AutoOping now disabled!\n");
		}

		return XCHAT_EAT_ALL;   /* eat this command so xchat and other plugins can't process it */
}

void xchat_plugin_get_info(char **name, char **desc, char **version, void **reserved)
{
		*name = PNAME;
		*desc = PDESC;
		*version = PVERSION;
}

int xchat_plugin_init(xchat_plugin *plugin_handle,
				char **plugin_name,
				char **plugin_desc,
				char **plugin_version,
				char *arg)
{
		/* we need to save this for use with any xchat_* functions */
		ph = plugin_handle;

		/* tell xchat our info */
		*plugin_name = PNAME;
		*plugin_desc = PDESC;
		*plugin_version = PVERSION;

		xchat_hook_command(ph, "AutoOpToggle", XCHAT_PRI_NORM, autooptoggle_cb, "Usage: AUTOOPTOGGLE, Turns OFF/ON Auto Oping", 0);
		xchat_hook_print(ph, "Join", XCHAT_PRI_NORM, join_cb, 0);

		xchat_print(ph, "AutoOpPlugin loaded successfully!\n");

		return 1;       /* return 1 for success */
}
