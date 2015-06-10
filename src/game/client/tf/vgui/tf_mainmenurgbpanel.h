#ifndef TFMAINMENURGBPANEL_H
#define TFMAINMENURGBPANEL_H

#include "tf_mainmenupanelbase.h"

class CTFMainMenuScrollBar;
//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
class CTFMainMenuRGBPanel : public CTFMainMenuPanelBase
{
	DECLARE_CLASS_SIMPLE(CTFMainMenuRGBPanel, CTFMainMenuPanelBase);

public:
	CTFMainMenuRGBPanel(vgui::Panel* parent, const char *panelName);
	virtual ~CTFMainMenuRGBPanel();

	void PerformLayout();
	void OnCommand(const char* command);
	virtual void ApplySchemeSettings(vgui::IScheme *pScheme);

private:

	CTFMainMenuScrollBar	*m_pRedScrollBar;
	CTFMainMenuScrollBar	*m_pGrnScrollBar;
	CTFMainMenuScrollBar	*m_pBluScrollBar;
	ImagePanel				*m_pColorBG;
};

#endif // TFMAINMENURGBPANEL_H