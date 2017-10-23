public:
	XmlReader() { x_InitMarkup(); SetDoc( NULL ); };
	XmlReader( MCD_CSTR szDoc ) { x_InitMarkup(); SetDoc( szDoc ); };
	XmlReader( int nFlags ) { x_InitMarkup(); SetDoc( NULL ); m_nDocFlags = nFlags; };
	XmlReader( const CMarkup& markup ) { x_InitMarkup(); *this = markup; };
	void operator=( const CMarkup& markup );
	~XmlReader();

	// Navigate
	bool Load( MCD_CSTR_FILENAME szFileName );
	bool ReadFromFile( MCD_CSTR_FILENAME szFileName ) { return Load( szFileName ); }
	bool SetDoc( MCD_PCSZ pDoc );
	bool SetDoc( const MCD_STR& strDoc );
	bool IsWellFormed();
	bool FindElem( MCD_CSTR szName = NULL );
	bool FindChildElem( MCD_CSTR szName = NULL );
	bool IntoElem();
	bool OutOfElem();
	void ResetChildPos() { x_SetPos( m_iPosParent, m_iPos, 0 ); };
	void ResetMainPos() { x_SetPos( m_iPosParent, 0, 0 ); };
	void ResetPos() { x_SetPos( 0, 0, 0 ); };
	MCD_STR GetTagName() const;
	MCD_STR GetChildTagName() const { return x_GetTagName( m_iPosChild ); };
	MCD_STR GetData() { return x_GetData( m_iPos ); };
	MCD_STR GetChildData() { return x_GetData( m_iPosChild ); };
	MCD_STR GetElemContent() const { return x_GetElemContent( m_iPos ); };
	MCD_STR GetAttrib( MCD_CSTR szAttrib ) const { return x_GetAttrib( m_iPos, szAttrib ); };
	MCD_STR GetChildAttrib( MCD_CSTR szAttrib ) const { return x_GetAttrib( m_iPosChild, szAttrib ); };
	bool GetNthAttrib( int n, MCD_STR& strAttrib, MCD_STR& strValue ) const;
	MCD_STR GetAttribName( int n ) const;
	int FindNode( int nType = 0 );
	int GetNodeType() { return m_nNodeType; };
	bool SavePos( MCD_CSTR szPosName = MCD_T( "" ), int nMap = 0 );
	bool RestorePos( MCD_CSTR szPosName = MCD_T( "" ), int nMap = 0 );
	bool SetMapSize( int nSize, int nMap = 0 );
	MCD_STR GetError() const;
	const MCD_STR& GetResult() const { return m_strResult; };
	int GetDocFlags() const { return m_nDocFlags; };
	void SetDocFlags( int nFlags ) { m_nDocFlags = ( nFlags & ~( MDF_READFILE | MDF_WRITEFILE | MDF_APPENDFILE ) ); };
	enum MarkupDocFlags
	{
		MDF_UTF16LEFILE = 1,
		MDF_UTF8PREAMBLE = 4,
		MDF_IGNORECASE = 8,
		MDF_READFILE = 16,
		MDF_WRITEFILE = 32,
		MDF_APPENDFILE = 64,
		MDF_UTF16BEFILE = 128,
		MDF_TRIMWHITESPACE = 256,
		MDF_COLLAPSEWHITESPACE = 512
	};
	enum MarkupNodeFlags
	{
		MNF_WITHCDATA = 0x01,
		MNF_WITHNOLINES = 0x02,
		MNF_WITHXHTMLSPACE = 0x04,
		MNF_WITHREFS = 0x08,
		MNF_WITHNOEND = 0x10,
		MNF_ESCAPEQUOTES = 0x100,
		MNF_NONENDED = 0x100000,
		MNF_ILLDATA = 0x200000
	};
	enum MarkupNodeType
	{
		MNT_ELEMENT = 1,    // 0x0001
		MNT_TEXT = 2,    // 0x0002
		MNT_WHITESPACE = 4,    // 0x0004
		MNT_TEXT_AND_WHITESPACE = 6,    // 0x0006
		MNT_CDATA_SECTION = 8,    // 0x0008
		MNT_PROCESSING_INSTRUCTION = 16,   // 0x0010
		MNT_COMMENT = 32,   // 0x0020
		MNT_DOCUMENT_TYPE = 64,   // 0x0040
		MNT_EXCLUDE_WHITESPACE = 123,  // 0x007b
		MNT_LONE_END_TAG = 128,  // 0x0080
		MNT_NODE_ERROR = 32768 // 0x8000
	};

	// Create
	bool Save( MCD_CSTR_FILENAME szFileName );
	bool WriteToFile( MCD_CSTR_FILENAME szFileName ) { return Save( szFileName ); }
	const MCD_STR& GetDoc() const { return m_strDoc; };
	bool AddElem( MCD_CSTR szName, MCD_CSTR szData = NULL, int nFlags = 0 ) { return x_AddElem( szName, szData, nFlags ); };
	bool InsertElem( MCD_CSTR szName, MCD_CSTR szData = NULL, int nFlags = 0 ) { return x_AddElem( szName, szData, nFlags | MNF_INSERT ); };
	bool AddChildElem( MCD_CSTR szName, MCD_CSTR szData = NULL, int nFlags = 0 ) { return x_AddElem( szName, szData, nFlags | MNF_CHILD ); };
	bool InsertChildElem( MCD_CSTR szName, MCD_CSTR szData = NULL, int nFlags = 0 ) { return x_AddElem( szName, szData, nFlags | MNF_INSERT | MNF_CHILD ); };
	bool AddElem( MCD_CSTR szName, int nValue, int nFlags = 0 ) { return x_AddElem( szName, nValue, nFlags ); };
	bool InsertElem( MCD_CSTR szName, int nValue, int nFlags = 0 ) { return x_AddElem( szName, nValue, nFlags | MNF_INSERT ); };
	bool AddChildElem( MCD_CSTR szName, int nValue, int nFlags = 0 ) { return x_AddElem( szName, nValue, nFlags | MNF_CHILD ); };
	bool InsertChildElem( MCD_CSTR szName, int nValue, int nFlags = 0 ) { return x_AddElem( szName, nValue, nFlags | MNF_INSERT | MNF_CHILD ); };
	bool AddAttrib( MCD_CSTR szAttrib, MCD_CSTR szValue ) { return x_SetAttrib( m_iPos, szAttrib, szValue ); };
	bool AddChildAttrib( MCD_CSTR szAttrib, MCD_CSTR szValue ) { return x_SetAttrib( m_iPosChild, szAttrib, szValue ); };
	bool AddAttrib( MCD_CSTR szAttrib, int nValue ) { return x_SetAttrib( m_iPos, szAttrib, nValue ); };
	bool AddChildAttrib( MCD_CSTR szAttrib, int nValue ) { return x_SetAttrib( m_iPosChild, szAttrib, nValue ); };
	bool AddSubDoc( MCD_CSTR szSubDoc ) { return x_AddSubDoc( szSubDoc, 0 ); };
	bool InsertSubDoc( MCD_CSTR szSubDoc ) { return x_AddSubDoc( szSubDoc, MNF_INSERT ); };
	MCD_STR GetSubDoc() { return x_GetSubDoc( m_iPos ); };
	bool AddChildSubDoc( MCD_CSTR szSubDoc ) { return x_AddSubDoc( szSubDoc, MNF_CHILD ); };
	bool InsertChildSubDoc( MCD_CSTR szSubDoc ) { return x_AddSubDoc( szSubDoc, MNF_CHILD | MNF_INSERT ); };
	MCD_STR GetChildSubDoc() { return x_GetSubDoc( m_iPosChild ); };
	bool AddNode( int nType, MCD_CSTR szText ) { return x_AddNode( nType, szText, 0 ); };
	bool InsertNode( int nType, MCD_CSTR szText ) { return x_AddNode( nType, szText, MNF_INSERT ); };

	// Modify
	bool RemoveElem();
	bool RemoveChildElem();
	bool RemoveNode();
	bool SetAttrib( MCD_CSTR szAttrib, MCD_CSTR szValue, int nFlags = 0 ) { return x_SetAttrib( m_iPos, szAttrib, szValue, nFlags ); };
	bool SetChildAttrib( MCD_CSTR szAttrib, MCD_CSTR szValue, int nFlags = 0 ) { return x_SetAttrib( m_iPosChild, szAttrib, szValue, nFlags ); };
	bool SetAttrib( MCD_CSTR szAttrib, int nValue, int nFlags = 0 ) { return x_SetAttrib( m_iPos, szAttrib, nValue, nFlags ); };
	bool SetChildAttrib( MCD_CSTR szAttrib, int nValue, int nFlags = 0 ) { return x_SetAttrib( m_iPosChild, szAttrib, nValue, nFlags ); };
	bool SetData( MCD_CSTR szData, int nFlags = 0 ) { return x_SetData( m_iPos, szData, nFlags ); };
	bool SetChildData( MCD_CSTR szData, int nFlags = 0 ) { return x_SetData( m_iPosChild, szData, nFlags ); };
	bool SetData( int nValue ) { return x_SetData( m_iPos, nValue ); };
	bool SetChildData( int nValue ) { return x_SetData( m_iPosChild, nValue ); };
	bool SetElemContent( MCD_CSTR szContent ) { return x_SetElemContent( szContent ); };


	// Utility
	static bool ReadTextFile( MCD_CSTR_FILENAME szFileName, MCD_STR& strDoc, MCD_STR* pstrResult = NULL, int* pnDocFlags = NULL, MCD_STR* pstrEncoding = NULL );
	static bool WriteTextFile( MCD_CSTR_FILENAME szFileName, const MCD_STR& strDoc, MCD_STR* pstrResult = NULL, int* pnDocFlags = NULL, MCD_STR* pstrEncoding = NULL );
	static MCD_STR EscapeText( MCD_CSTR szText, int nFlags = 0 );
	static MCD_STR UnescapeText( MCD_CSTR szText, int nTextLength = -1, int nFlags = 0 );
	static int UTF16To8( char *pszUTF8, const unsigned short* pwszUTF16, int nUTF8Count );
	static int UTF8To16( unsigned short* pwszUTF16, const char* pszUTF8, int nUTF8Count );
	static MCD_STR UTF8ToA( MCD_CSTR pszUTF8, int* pnFailed = NULL );
	static MCD_STR AToUTF8( MCD_CSTR pszANSI );
	static void EncodeCharUTF8( int nUChar, char* pszUTF8, int& nUTF8Len );
	static int DecodeCharUTF8( const char*& pszUTF8, const char* pszUTF8End = NULL );
	static void EncodeCharUTF16( int nUChar, unsigned short* pwszUTF16, int& nUTF16Len );
	static int DecodeCharUTF16( const unsigned short*& pwszUTF16, const unsigned short* pszUTF16End = NULL );
	static bool DetectUTF8( const char* pText, int nTextLen, int* pnNonASCII = NULL, bool* bErrorAtEnd = NULL );
	static MCD_STR GetDeclaredEncoding( MCD_CSTR szDoc );
	static int GetEncodingCodePage( MCD_CSTR pszEncoding );
