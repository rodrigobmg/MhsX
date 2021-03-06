#pragma once

#include "../LSWWin.h"
#include "../Widget/LSWWidget.h"

namespace lsw {

	class CComboBox : public CWidget {
	public :
		CComboBox( const LSW_WIDGET_LAYOUT &_wlLayout, CWidget * _pwParent, bool _bCreateWidget = true, HMENU _hMenu = NULL );


		// == Functions.
		// Adds a string to a list in a combo box. If the combo box does not have the CBS_SORT style, the
		//	string is added to the end of the list. Otherwise, the string is inserted into the list and the list is sorted.
		INT									AddString( LPCSTR _psString );

		// Adds a string to a list in a combo box. If the combo box does not have the CBS_SORT style, the
		//	string is added to the end of the list. Otherwise, the string is inserted into the list and the list is sorted.
		INT									AddString( LPCWSTR _pwsString );

		// Deletes the item at the specified location in a list in a combo box.
		INT									DeleteString( INT  _iIndex );

		// Gets the number of items in the list box of a combo box.
		INT									GetCount() const;

		// Gets the length of an item's text.
		INT									GetLBTextLen( INT _iIndex ) const;

		// Gets a string from a list in a combo box.
		INT									GetLBText( INT _iIndex, std::wstring &_wString ) const;

		// Gets the index of the currently selected item in a combo box.
		INT									GetCurSel() const;

		// Gets the application-defined value associated with the specified list item in a combo box.
		LRESULT								GetItemData( INT _iIndex ) const;

		// Retrieves the height of list items in a combo box.
		INT									GetItemHeight() const;

		// Gets the minimum number of visible items in the drop-down list of a combo box.
		INT									GetMinVisible() const;

		// Adds a string to a list in a combo box at the specified location.
		INT									InsertString( INT _iIndex, LPCSTR _lpStr );

		// Adds a string to a list in a combo box at the specified location.
		INT									InsertString( INT _iIndex, LPCWSTR _lpStr );

		// Removes all items from the list box and edit control of a combo box.
		VOID								ResetContent();

		// Sets the application-defined value associated with the specified list item in a combo box.
		INT									SetItemData( INT _iIndex, LPARAM _pData );

		// Sets the height of list items or the selection field in a combo box.  If the index or height is invalid, the return value is CB_ERR.
		INT									SetItemHeight( INT _iIndex, INT _cyItem );

		// Sets the minimum number of visible items in the drop-down list of a combo box.
		BOOL								SetMinVisible( INT _iMinVisible );

		// Shows or hides the list in a combo box.
		BOOL								ShowDropdown( BOOL _fShow );

		// Gets the rectangle for a string in the combo bod.
		LSW_RECT							GetItemRect( INT _iIndex ) const;

		// Gets the minimum width for the list box.
		LONG								GetListMinWidth() const;

		// Auto-sets the minimum width of the list box after adding all the strings.
		LONG								AutoSetMinListWidth();


	private :
		typedef CWidget						Parent;
	};

}	// namespace lsw
