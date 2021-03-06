#pragma once
#include "MXOptionsPage.h"
#include "MXOptions.h"
#include <ListBox/LSWListBox.h>
#include <LSWWin.h>
#include <MainWindow/LSWMainWindow.h>

using namespace lsw;

namespace mx {

	class COptionsWindow : public lsw::CMainWindow {
	public :
		COptionsWindow( const LSW_WIDGET_LAYOUT &_wlLayout, CWidget * _pwParent, MX_OPTIONS * _poOptions, bool _bCreateWidget = true, HMENU _hMenu = NULL );


		// == Functions.
		// WM_INITDIALOG.
		virtual LSW_HANDLED					InitDialog();

		// WM_COMMAND from control.
		virtual LSW_HANDLED					Command( WORD _wCtrlCode, WORD _Id, CWidget * _pwSrc );

		// WM_CLOSE.
		virtual LSW_HANDLED					Close();


	protected :
		// == Members.
		// Options pages.
		std::vector<COptionsPage *>			m_vPages;

		// Options.
		MX_OPTIONS *						m_poOptions;


		// == Functions.
		// Sets the page by index.
		void								SetPage( DWORD _dwIndex );

		// Gets the list box pointer.
		CListBox *							ListBox();
	};

}	// namespace mx
