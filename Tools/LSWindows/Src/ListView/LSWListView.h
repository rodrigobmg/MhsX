#pragma once

#include "../LSWWin.h"
#include "../Widget/LSWWidget.h"

namespace lsw {

	class CListView : public CWidget {
	public :
		CListView( const LSW_WIDGET_LAYOUT &_wlLayout, CWidget * _pwParent, bool _bCreateWidget = true, HMENU _hMenu = NULL );


		// == Functions.
		// Set sort case sensitivity.
		VOID								SetSortCaseSensitivity( BOOL _bVal ) { m_bSortWithCase = (_bVal != FALSE); }

		// If the list-view control was created without the LVS_OWNERDATA style, this macro causes the control to allocate its internal data structures for
		//	the specified number of items. This prevents the control from having to allocate the data structures every time an item is added.
		VOID								SetItemCount( INT _cItems );

		// Gets the number of columns.
		INT									GetTotalColumns() const;

		// Inserts a column at the given index.
		INT									InsertColumn( INT _iIndex, const WCHAR * _pwcText, INT _iFormat = LVCFMT_LEFT );

		// Inserts a column at the given index.
		INT									InsertColumn( INT _iIndex, const CHAR * _pcText, INT _iFormat = LVCFMT_LEFT );

		// Adds a column with the given text.
		INT									AddColumn( const CHAR * _pcText, INT _iFormat = LVCFMT_LEFT );

		// Adds a column with the given text.
		INT									AddColumn( const WCHAR * _pwcText, INT _iFormat = LVCFMT_LEFT );

		// Sets the width of a column.
		BOOL								SetColumnWidth( INT _iCol, INT _iWidth );

		// Inserts an item.  Returns the index of the item.
		INT									InsertItem( const LVITEMW &_iItem );

		// Inserts an item.  Returns the index of the item.
		INT									InsertItem( const LVITEMA &_iItem );

		// Inserts an item that consistes of text and a parameter.
		INT									InsertItem( const WCHAR * _pwcText, LPARAM _lParam );

		// Inserts an item that consistes of text and a parameter.
		INT									InsertItem( const CHAR * _pcText, LPARAM _lParam );

		// Sets the text for an item.
		VOID								SetItemText( INT _iItem, INT _iSubItem, const WCHAR * _pwcText );

		// Sets the text for an item.
		VOID								SetItemText( INT _iItem, INT _iSubItem, const CHAR * _pcText );

		// Gets the length of an item's text in WCHAR units.
		INT									GetItemTextLenW( INT _iItem, INT _iSubItem );

		// Gets the length of an item's text in CHAR units.
		INT									GetItemTextLenA( INT _iItem, INT _iSubItem );

		// Gets the text of an item.
		VOID								GetItemText( INT _iItem, INT _iSubItem, std::wstring &_sRet );

		// Gets the text of an item.
		VOID								GetItemText( INT _iItem, INT _iSubItem, std::string &_sRet );

		// Gets the index of the (first) selected item or -1.
		INT									GetFirstSelectedItem();

		// Gets the data of the selected item or returns -1.
		LPARAM								GetSelData();

		// Gets an item.  _iItm is input and output.
		BOOL								GetItem( INT _iItem, INT _iSubItem, LVITEMW &_iItm );

		// Gets an item.  _iItm is input and output.
		BOOL								GetItem( INT _iItem, INT _iSubItem, LVITEMA &_iItm );

		// Sort items.
		virtual BOOL						SortItems( INT _iSubItem );

		// Sort comparison function.  Override to change how items compare against each other.
		virtual int							SortCompare( INT _iLeft, INT _iRight, INT _iSub );

		// Delete all items.
		virtual VOID						DeleteAll();


	protected :
		// == Types.
		struct LSW_LISTSORT {
			CListView *						plvListView;
			INT								iSubItem;
		};

		// == Members.
		// The number of columns.
		SIZE_T								m_sColumns;

		// Sort with case-sensitivity or not.
		BOOL								m_bSortWithCase;


		// == Functions.
		// Setting the HWND after the control has been created.
		virtual void						InitControl( HWND _hWnd );

		// Sort routine.
		static int CALLBACK					CompareFunc( LPARAM _lParam1, LPARAM _lParam2, LPARAM _lParamSort );


	private :
		typedef CWidget						Parent;
	};

}	// namespace lsw
