
#ifndef __LIB_H
#define __LIB_H

/*
    ��Ȩ������
    ���ļ���ȨΪ�����������������У�����Ȩ����������������������֧�ֿ⣬��ֹ���������κγ��ϡ�
*/

// ��������ϵͳ����Ļ����������ͣ������ٸ��ġ�

#define		_SDT_NULL		0           // �հ���������
#define		_SDT_ALL		MAKELONG (MAKEWORD (0, 0), 0x8000)		// ͨ����
	/*  ������֧�ֿ������������򷵻�ֵ���������ͣ������ڶ�����������ʱ��
	_SDT_ALL����ƥ�������������ͣ��������ͱ������Ҫ�󣩡�*/
#define		SDT_BYTE		MAKELONG (MAKEWORD (1, 1), 0x8000)		// �ֽ�
#define		SDT_SHORT		MAKELONG (MAKEWORD (1, 2), 0x8000)		// ������
#define		SDT_INT			MAKELONG (MAKEWORD (1, 3), 0x8000)		// ����
#define		SDT_INT64		MAKELONG (MAKEWORD (1, 4), 0x8000)		// ������
#define		SDT_FLOAT		MAKELONG (MAKEWORD (1, 5), 0x8000)		// С��
#define		SDT_DOUBLE		MAKELONG (MAKEWORD (1, 6), 0x8000)		// ˫����С��
#define		SDT_BOOL		MAKELONG (MAKEWORD (2, 0), 0x8000)		// �߼�
#define		SDT_DATE_TIME	MAKELONG (MAKEWORD (3, 0), 0x8000)		// ����ʱ��
#define		SDT_TEXT		MAKELONG (MAKEWORD (4, 0), 0x8000)		// �ı�
#define		SDT_BIN			MAKELONG (MAKEWORD (5, 0), 0x8000)		// �ֽڼ�
#define		SDT_SUB_PTR		MAKELONG (MAKEWORD (6, 0), 0x8000)		// ��¼�û��������ӳ���Ĵ����ַ

// ���������������͵����
#define	DTM_SYS_DATA_TYPE_MASK		0x80000000
#define	DTM_USER_DATA_TYPE_MASK		0x40000000
#define	DTM_LIB_DATA_TYPE_MASK		0x00000000

// �����������е������־�����ĳ��������ֵ��λ��1�����ʾΪ���������͵����顣
// ����־������������ʱΪ����AS_RECEIVE_VAR_OR_ARRAY��AS_RECEIVE_ALL_TYPE_DATA
// ��־�Ŀ��������˵����Ϊ�Ƿ�Ϊ�������ݣ��������Ͼ�δʹ�á���������ط���
// ���Ժ��Ա���־��
#define	DT_IS_ARY					0x20000000

typedef DWORD DATA_TYPE;
typedef DATA_TYPE* PDATA_TYPE;

typedef struct
{
	LPTSTR		m_szName;				// ��������
	LPTSTR		m_szExplain;			// ������ϸ����
	SHORT		m_shtBitmapIndex;		// �μ� CMD_INFO �е�ͬ����Ա
	SHORT		m_shtBitmapCount;		// �μ� CMD_INFO �е�ͬ����Ա

	DATA_TYPE	m_dtDataType;           // ��������������

	INT			m_nDefault;
		// ϵͳ�������Ͳ�����Ĭ��ָ��ֵ���ڱ���ʱ���������Զ�������
		//     1����ֵ�ͣ�ֱ��Ϊ��ֵ����ΪС����ֻ��ָ�����������֣�
		//		  ��Ϊ��������ֻ��ָ��������INT��ֵ�Ĳ��֣���
		//     2���߼��ͣ�1�����棬0���ڼ٣�
		//     3���ı��ͣ�����Ա��ʱΪLPTSTRָ�룬ָ��Ĭ���ı�����
		//     4�������������Ͳ���һ����Ĭ��ָ��ֵ��

	#define		AS_HAS_DEFAULT_VALUE				(1 << 0)
			// ��������Ĭ��ֵ��Ĭ��ֵ��m_nDefault��˵�������±�־���⡣
	#define		AS_DEFAULT_VALUE_IS_EMPTY			(1 << 1)
			// ��������Ĭ��ֵ��Ĭ��ֵΪ�գ����ϱ�־���⡣
    // ���������־ͬʱֻ����һ����λ��
	#define		AS_RECEIVE_VAR					    (1 << 2)
			// Ϊ�������ṩ����ʱ�����ṩ��������������
	#define		AS_RECEIVE_VAR_ARRAY				(1 << 3)
			// Ϊ�������ṩ����ʱ�����ṩ������������
	#define		AS_RECEIVE_VAR_OR_ARRAY			    (1 << 4)
			// Ϊ�������ṩ����ʱ�����ṩ������������������
	#define		AS_RECEIVE_ARRAY_DATA			    (1 << 5)
			// Ϊ�������ṩ����ʱ�����ṩ���������ݡ�
	#define		AS_RECEIVE_ALL_TYPE_DATA            (1 << 6)
			// Ϊ�������ṩ����ʱ�����ṩ��������������ݡ�
	DWORD		m_dwState;
}
ARG_INFO, *PARG_INFO;

struct CMD_INFO
{
	LPTSTR		m_szName;			// ������������
	LPTSTR		m_szEGName;			// ����Ӣ�����ƣ�����Ϊ�ջ�NULL��

	LPTSTR		m_szExplain;		// ������ϸ����
	SHORT		m_shtCategory;		// ȫ�������������𣬴�1��ʼ����һ���ֵΪָ��LIB_INFO��
                                    // m_szzCategory��Ա���ṩ��ĳ������ַ�����������
                                    // �����Ա����Ĵ�ֵΪ-1��

	#define		CT_IS_HIDED					(1 << 2)
		//   �������Ƿ�Ϊ�������������Ҫ���û�ֱ������������ѭ����������򱻷���
	    // ��Ϊ�˱��ּ�������Ҫ���ڵ������
	#define		CT_IS_ERROR					(1 << 3)
		// �������ڱ����в���ʹ�ã����д˱�־һ����������Ҫ�����ڲ�ͬ���԰汾����ͬ����ʹ�ã�
		// ����A������A���԰汾���п�����Ҫʵ�ֲ�ʹ�ã�����B���԰汾���п��ܾͲ���Ҫ�����
		// ������ʹ���˾��д˱�־�������ֻ��֧�ָó������ͱ��룬������֧�����С�
		// ����д˱�־�����Բ�ʵ�ֱ������ִ�в��֡�
	#define		CT_DISABLED_IN_RELEASE_VER	(1 << 4)
		// ���б���־��������������ϵͳ����RELEASE���׳���ʱ������������������������޷���ֵ��
	#define		CT_ALLOW_APPEND_NEW_ARG		(1 << 5)
		//   �ڱ�����Ĳ������ĩβ�Ƿ��������µĲ������²�����ͬ�ڲ������е����һ��������
	#define		CT_RETURN_ARRAY_DATA		(1 << 6)
		// ����˵��m_dtRetType��˵���Ƿ�Ϊ�����������ݡ�
	WORD		m_wState;

	/*  !!!!! ǧ��ע�⣺�������ֵ���Ͷ���Ϊ _SDT_ALL �����Բ��ܷ�������(��CT_RETURN_ARRAY_DATA
		��λ)�򸴺��������͵�����(���û�����Զ����������͵����������ڻ�˵���Ԫ)��
		��Ϊ�û������޷��Զ�ɾ������������������Ķ���ռ�(���ı��ͻ����ֽڼ��ͳ�Ա��)�� */
	DATA_TYPE	m_dtRetType;    // ����ֵ���͡�

	WORD		m_wReserved;    // ����������Ϊ0��

    // ����꣬����Ϊ�û��ṩѧϰ�Ѷ�˵����
    #define	LVL_SIMPLE			1		// ����
    #define	LVL_SECONDARY		2		// �м�
    #define	LVL_HIGH			3		// �߼�
	SHORT		m_shtUserLevel;	// ������û����𣬱���Ա��ֵΪ����ļ���ꡣ

	SHORT		m_shtBitmapIndex;	// ָ��ͼ����������1��ʼ��0��ʾ�ޡ���һ���ֵΪָ��֧�ֿ�����Ϊ
                                    // "LIB_BITMAP"��BITMAP��Դ��ĳһ����16X13λͼ��������
	SHORT		m_shtBitmapCount;	// ͼ����Ŀ(����ΪIDE�ṩ����ͼƬ).

	INT			m_nArgCount;		// ����Ĳ�����Ŀ
	PARG_INFO	m_pBeginArgInfo;    // ָ������Ĳ���������Ϣ����
};
typedef CMD_INFO* PCMD_INFO;

struct LIB_DATA_TYPE_ELEMENT
{
	DATA_TYPE m_dtDataType; // �����ݳ�Ա���������͡�

	LPBYTE m_pArySpec;  // �������ԱΪ���飬�򱾳�Ա�ṩ����ָ�����������ֵΪNULL��
        // ����ָ�����ĸ�ʽΪ������Ϊһ��BYTE��¼�������ά�������Ϊ0��ʾ��Ϊ���飬���ֵΪ0x7f����
        // Ȼ��Ϊ��Ӧ��Ŀ��INTֵ˳���¼��Ӧά��Ԫ����Ŀ��

	LPTSTR m_szName;    // �����ݳ�Ա�����ƣ���������ݳ�Ա��������������ֻ����һ�����ݳ�Ա����ֵӦ��ΪNULL��
	LPTSTR m_szEGName;  // �����ݳ�Ա��Ӣ�����ƣ�����Ϊ�ջ�NULL��
	LPTSTR m_szExplain; // �����ݳ�Ա����ϸ˵����

	#define LES_HAS_DEFAULT_VALUE  (1 << 0)    // �����ݳ�Ա��Ĭ��ֵ��Ĭ��ֵ��m_nDefault��˵����
	DWORD m_dwState;

    // ���� m_dwState ���� LES_HAS_DEFAULT_VALUE ��־�ҷ�����ʱ����Ч��
	INT m_nDefault;
		// �����ݳ�Ա��Ĭ��ָ��ֵ��
		//     1����ֵ�ͣ�ֱ��Ϊ��ֵ����ΪС����ֻ��ָ�����������֣�
		//		  ��Ϊ��������ֻ��ָ��������INT��ֵ�Ĳ��֣���
		//     2���߼��ͣ�1�����棬0���ڼ٣�
		//     3���ı��ͣ���������ʱΪLPTSTRָ�룬ָ��Ĭ���ı�����
		//     4�������������Ͳ���һ����Ĭ��ָ��ֵ��
};
typedef LIB_DATA_TYPE_ELEMENT* PLIB_DATA_TYPE_ELEMENT;

// �̶����Ե���Ŀ
#define	FIXED_WIN_UNIT_PROPERTY_COUNT	8

// ÿ���̶����Զ���
#define	FIXED_WIN_UNIT_PROPERTY	\
	{	_WT("���"), _WT("left"),	NULL,	UD_INT,	NULL,	NULL	},	\
	{	_WT("����"), _WT("top"),	NULL,	UD_INT,	NULL,	NULL	},	\
	{	_WT("���"), _WT("width"),	NULL,	UD_INT,	NULL,	NULL	},	\
	{	_WT("�߶�"), _WT("height"),	NULL,	UD_INT,	NULL,	NULL	},	\
	{	_WT("���"), _WT("tag"),	NULL,	UD_TEXT,	NULL,	NULL	},	\
	{	_WT("����"), _WT("visible"),	NULL,	UD_BOOL,	NULL,	NULL	},	\
	{	_WT("��ֹ"), _WT("disable"),	NULL,	UD_BOOL,	NULL,	NULL	},	\
	{	_WT("���ָ��"), _WT("MousePointer"),	NULL,	UD_CURSOR,	NULL,	NULL	}

// �������崰�ڵ�Ԫ���ԡ�
struct UNIT_PROPERTY
{
	LPTSTR m_szName;    // �������ƣ�ע��Ϊ���������Ա���ͬʱ���ö��������ԣ���ͬ�������Ե��������һ�¡�
	LPTSTR m_szEGName;  // Ӣ�����ơ�
	LPTSTR m_szExplain; // ���Խ��͡�

	#define		UD_INT			    1001	// ����ΪINTֵ
	#define		UD_DOUBLE		    1002	// ����ΪDOUBLEֵ
	#define		UD_BOOL			    1003	// ����ΪBOOLֵ
	#define		UD_DATE_TIME	    1004	// ����ΪDATEֵ
	#define		UD_TEXT			    1005	// ����Ϊ�ַ���
	#define		UD_PICK_INT			1006	// ����ΪINTֵ���û�ֻ��ѡ�񣬲��ܱ༭��
	#define		UD_PICK_TEXT		1007	// ����Ϊ��ѡ�ַ������û�ֻ��ѡ�񣬲��ܱ༭��
	#define		UD_EDIT_PICK_TEXT	1008	// ����Ϊ��ѡ�ַ������û����Ա༭��
	#define		UD_PIC			    1009	// ΪͼƬ�ļ�����
	#define		UD_ICON			    1010	// Ϊͼ���ļ�����
	#define		UD_CURSOR		    1011
		//   ��һ��INT��¼���ָ�����ͣ�����ֵ�� Windows API �� LoadCursor ������
        // ��Ϊ-1����Ϊ�Զ������ָ�룬��ʱ�����Ӧ���ȵ����ָ���ļ����ݡ�
	#define		UD_MUSIC		    1012	// Ϊ�����ļ�����
	#define		UD_FONT			    1013    // Ϊһ��LOGFONT���ݽṹ�������ٸġ�
	#define		UD_COLOR		    1014    // ����ΪCOLORREFֵ��
	#define		UD_COLOR_TRANS	    1015
		//   ����ΪCOLORREFֵ������͸����ɫ(��CLR_DEFAULT����CLR_DEFAULT��
        // VC++��COMMCTRL.Hͷ�ļ��ж���)��
	#define		UD_FILE_NAME	    1016
		//   ����Ϊ�ļ����ַ�������ʱm_szzPickStr�е�����Ϊ��
		// �Ի������ + "\0" + �ļ��������� + "\0" + Ĭ�Ϻ�׺ + "\0" +
		// "1"��ȡ�����ļ�������"0"��ȡ�����ļ����� + "\0"
	#define		UD_COLOR_BACK	    1017
		// ����ΪCOLORREFֵ������ϵͳĬ�ϱ�����ɫ(��CLR_DEFAULT����)��
	#define		UD_ODBC_CONNECT_STR	1021
		// ODBC���������ı�
	#define		UD_ODBC_SELECT_STR	1022
		// ODBC���ݲ�ѯSQL�ı�
	#define		UD_IMAGE_LIST		1023
		// ͼƬ�飬���ݽṹΪ��
		#define	IMAGE_LIST_DATA_MARK	(MAKELONG ('IM', 'LT'))
		/*
		DWORD: ��־���ݣ�Ϊ IMAGE_LIST_DATA_MARK
		COLORREF: ͸����ɫ������ΪCLR_DEFAULT��
		����ΪͼƬ�����ݣ���CImageList::Read��CImageList::Write��д��
		*/
	#define		UD_CUSTOMIZE		1024    // �Զ�����������

	SHORT m_shtType;	// ���Ե��������ͣ�Ϊ����ĺ�ֵ����

	#define	UW_HAS_INDENT		(1 << 0)	// �����Ա�����ʾʱ��������һ�Σ�һ�����������ԡ�
	#define	UW_GROUP_LINE		(1 << 1)	// �����Ա��б���������ʾ����׷��ߡ�
	#define	UW_ONLY_READ		(1 << 2)    // ֻ�����ԣ����ʱ�����ã�����ʱ����д��
	#define	UW_CANNOT_INIT		(1 << 3)    // ���ʱ�����ã�������ʱ����������д�����ϱ�־���⡣
	WORD m_wState;

	LPTSTR m_szzPickStr;
		// ��m_nTypeΪUP_PICK_INT��UP_PICK_TEXT��UD_EDIT_PICK_TEXT��UD_FILE_NAMEʱ����ΪNULL��
		// ˳���¼��"\0"�ָ������б�ѡ�ı�������UD_FILE_NAMEΪ��˵���������ʽ���������һ��"\0"������
};
typedef UNIT_PROPERTY* PUNIT_PROPERTY;

typedef struct
{
	LPTSTR		m_szName;       // ��������
	LPTSTR		m_szExplain;    // ������ϸ����

	#define EAS_IS_BOOL_ARG     (1 << 0)	// Ϊ�߼��Ͳ��������޴˱�־������Ϊ�������Ͳ���
	DWORD		m_dwState;
}
EVENT_ARG_INFO, *PEVENT_ARG_INFO;

struct EVENT_INFO
{
	LPTSTR		m_szName;			// �¼�����
	LPTSTR		m_szExplain;		// �¼���ϸ����

	#define		EV_IS_HIDED			(1 << 0)
    	// ���¼��Ƿ�Ϊ�����¼��������ܱ�һ���û���ʹ�û򱻷�����Ϊ�˱��ּ�������Ҫ���ڵ��¼�����
	#define		EV_RETURN_INT		(1 << 3)
        // ���¼��Ĵ����ӳ�����Ҫ����һ��������
	#define		EV_RETURN_BOOL		(1 << 4)
        // ���¼��Ĵ����ӳ�����Ҫ����һ���߼�ֵ�����ϱ�־���⡣
	DWORD		m_dwState;

	INT				m_nArgCount;		// �¼��Ĳ�����Ŀ
	PEVENT_ARG_INFO	m_pEventArgInfo;	// �¼�����
};
typedef EVENT_INFO* PEVENT_INFO;

////////////////////////////////////

typedef DWORD  HUNIT;

// ͨ�ýӿ�ָ�롣
typedef void (WINAPI *PFN_INTERFACE) ();

// ���ڵ�Ԫ����ӿ�ID��
#define	ITF_CREATE_UNIT					1	// ������Ԫ
// ���������ӿڽ��ڿ��ӻ���ƴ��ڽ���ʱʹ�á�
#define	ITF_PROPERTY_UPDATE_UI			2	// ˵������Ŀǰ�ɷ��޸�
#define	ITF_DLG_INIT_CUSTOMIZE_DATA		3	// ʹ�öԻ��������Զ�������
#define	ITF_NOTIFY_PROPERTY_CHANGED		4	// ֪ͨĳ�������ݱ��޸�
#define	ITF_GET_ALL_PROPERTY_DATA		5	// ȡȫ����������
#define	ITF_GET_PROPERTY_DATA			6	// ȡĳ��������
#define	ITF_IS_NEED_THIS_KEY			8	//   ѯ�ʵ�Ԫ�Ƿ���Ҫָ���İ�����Ϣ���������ڵ�Ԫ
                                        	// �ػ���Ĭ��Ϊ����ʱ��������İ�������TAB��
                                            // SHIFT+TAB��UP��DOWN�ȡ�

typedef PFN_INTERFACE (WINAPI *PFN_GET_INTERFACE) (INT nInterfaceNO);

//////////////////////////////////// �ӿڣ�

// ������Ԫ���ɹ�ʱ����HUNIT��ʧ�ܷ���NULL��
typedef HUNIT (WINAPI *PFN_CREATE_UNIT) (
        LPBYTE pAllPropertyData,            //   ָ�򱾴��ڵ�Ԫ�������������ݣ��ɱ����ڵ�Ԫ��
                                            // ITF_GET_PROPERTY_DATA�ӿڲ��������û��������ΪNULL��
        INT nAllPropertyDataSize,           //   �ṩpAllPropertyData��ָ�����ݵĳߴ磬���û����Ϊ0��
		DWORD dwStyle,                      //   Ԥ�����õĴ��ڷ��
        HWND hParentWnd,                    //   �����ھ����
        UINT uID,                           //   �ڸ������е�ID��
        HMENU hMenu,                        //   δʹ�á�
        INT x, INT y, INT cx, INT cy,       //   ָ��λ�ü��ߴ硣
		DWORD dwWinFormID, DWORD dwUnitID,  //   �����ڵ�Ԫ���ڴ��ڼ������ID������֪ͨ��ϵͳ��
		HWND hDesignWnd ,                //   ���blInDesignModeΪ�棬��hDesignWnd�ṩ����ƴ��ڵĴ��ھ����
        BOOL blInDesignMode);       //   ˵���Ƿ�������IDE�����Խ��п��ӻ���ƣ�����ʱΪ�١�

// ���ָ������Ŀǰ���Ա������������棬���򷵻ؼ١�
typedef BOOL (WINAPI *PFN_PROPERTY_UPDATE_UI) (
        HUNIT hUnit,            // ��PFN_CREATE_UNIT���ص��Ѵ������ڵ�Ԫ�ľ������ͬ��
        INT nPropertyIndex);    // ����Ҫ��ѯ���Ե�����ֵ����ͬ��

// ������������ΪUD_CUSTOMIZE�ĵ�Ԫ���ԡ�
// �����Ҫ���´����õ�Ԫ�����޸ĵ�Ԫ���Σ��뷵���档
typedef BOOL (WINAPI *PFN_DLG_INIT_CUSTOMIZE_DATA) (
        HUNIT hUnit,
        INT nPropertyIndex,
		BOOL* pblModified ,   //   ���pblModified��ΪNULL���������з����Ƿ�
                                    // ���û������޸ģ�����������IDE����UNDO��¼����
        LPVOID pReserved );   // ����δ�á�

// ������¼ĳ���Եľ�������ֵ��
union UNIT_PROPERTY_VALUE
{
	INT			m_int;			// ��Ӧ���������UD_INT��UD_PICK_INT����ͬ��
	DOUBLE		m_double;		// UD_DOUBLE
	BOOL		m_bool;			// UD_BOOL
	DATE		m_dtDateTime;	// UD_DATE_TIME
	COLORREF	m_clr;			// UD_COLOR��UD_COLOR_TRANS��UD_COLOR_BACK

	LPTSTR		m_szText;		//   UD_TEXT��UD_PICK_TEXT��UD_EDIT_PICK_TEXT��
			                    // UD_ODBC_CONNECT_STR��UD_ODBC_SELECT_STR

	LPTSTR		m_szFileName;	// UD_FILE_NAME

    // UD_PIC��UD_ICON��UD_CURSOR��UD_MUSIC��UD_FONT��UD_CUSTOMIZE��UD_IMAGE_LIST
	struct
	{
		LPBYTE  m_pData;
		INT     m_nDataSize;
	} m_data;

	UNIT_PROPERTY_VALUE ()
	{
		memset ((LPBYTE)this, 0, sizeof (UNIT_PROPERTY_VALUE));
	}
};
typedef UNIT_PROPERTY_VALUE* PUNIT_PROPERTY_VALUE;

//   ֪ͨĳ���ԣ���UD_CUSTOMIZE������ԣ����ݱ��û��޸ģ���Ҫ���ݸ��޸���Ӧ����
// �ڲ����ݼ����Σ����ȷʵ��Ҫ���´��������޸ĵ�Ԫ���Σ��뷵���档
//   ע�⣺�������������ֵ�ĺϷ���У�顣
typedef BOOL (WINAPI *PFN_NOTIFY_PROPERTY_CHANGED) (
        HUNIT hUnit,
        INT nPropertyIndex,
		PUNIT_PROPERTY_VALUE pPropertyValue,    // �����޸ĵ���Ӧ�������ݡ�
        LPTSTR* ppszTipText);    // Ŀǰ��δʹ�á�

// ȡĳ�������ݵ�pPropertyValue�У��ɹ������棬���򷵻ؼ١�
/*  ע�⣺��������ʱ���ɵ���PFN_CREATE_UNITʱ��blInDesignMode������������
pPropertyValue���뷵�����洢��ֵ�����������ʱ��blInDesignModeΪ�٣�������
����ʵ�ʵĵ�ǰʵʱֵ��
    ����˵���༭�򴰿ڵ�Ԫ�ġ����ݡ����ԣ����ʱ���뷵���ڲ��������ֵ����
����ʱ�ͱ������ GetWindowText ȥʵʱ��ȡ�� */
typedef BOOL (WINAPI *PFN_GET_PROPERTY_DATA) (
        HUNIT hUnit,
        INT nPropertyIndex,
		PUNIT_PROPERTY_VALUE pPropertyValue);   // ������������ȡ���Ե����ݡ�

//   ���ر����ڵ�Ԫ��ȫ���������ݣ��ɸô��ڵ�Ԫ��ʵ�ִ���������Ƹ�ʽ��
// ��������������ϵ�һ�𡣴˴��ڵ�Ԫ��PFN_CREATE_UNIT�ӿڱ����ܹ���ȷ��
// �������ݡ�
typedef HGLOBAL (WINAPI *PFN_GET_ALL_PROPERTY_DATA) (HUNIT hUnit);

// ѯ�ʵ�Ԫ�Ƿ���Ҫָ���İ�����Ϣ�������Ҫ�������棬���򷵻ؼ١�
typedef BOOL (WINAPI *PFN_IS_NEED_THIS_KEY) (
        HUNIT hUnit,
        WORD wKey);

////////////////////////////////////

#define	UNIT_BMP_SIZE			24		// ��Ԫ��־λͼ�Ŀ�Ⱥ͸߶ȡ�
#define	UNIT_BMP_BACK_COLOR		(RGB (192, 192, 192))	// ��Ԫ��־λͼ�ı�����ɫ��

struct LIB_DATA_TYPE_INFO  // �ⶨ���������ͽṹ
{
	LPTSTR m_szName;    // ����
	LPTSTR m_szEGName;  // Ӣ�����ƣ���Ϊ�ջ�NULL��
	LPTSTR m_szExplain; // ��ϸ���ͣ��������ΪNULL��

	INT m_nCmdCount;        // ���������ͳ�Ա��������Ŀ����Ϊ0����
	LPINT m_pnCmdsIndex;	// ˳���¼�����������г�Ա����������֧�ֿ�������е�����ֵ����ΪNULL��

    //   �������Ƿ�Ϊ�������ͣ����������û�ֱ��������������ͣ��类����
    // ��Ϊ�˱��ּ�������Ҫ���ڵ����ͣ���
	#define		LDT_IS_HIDED				(1 << 0)
    // �������ڱ����в���ʹ�ã����д˱�־һ��������
    // ��ʹ���д˱�־�������͵���������Ҳ�����������塣
	#define		LDT_IS_ERROR				(1 << 1)
    // �Ƿ�Ϊ���ڵ�Ԫ����˱�־��λ��m_nElementCount��Ϊ0��
	#define		LDT_WIN_UNIT				(1 << 6)
    // �Ƿ�Ϊ�����ʹ��ڵ�Ԫ�����д˱�־��LDT_WIN_UNIT������λ��
	#define		LDT_IS_CONTAINER			(1 << 7)
    // �Ƿ�Ϊ�������ṩ���ܵĴ��ڵ�Ԫ����ʱ�ӣ�����˱�־��λ��LDT_WIN_UNIT����λ��
    // ���д˱�־�ĵ�Ԫ������ʱ�޿������Ρ�
	#define		LDT_IS_FUNCTION_PROVIDER	(1 << 15)
    // ���������ڵ�Ԫ����˱�־��λ���ʾ�˵�Ԫ���ܽ������뽹�㣬����TAB��ͣ����
	#define		LDT_CANNOT_GET_FOCUS		(1 << 16)
    // ���������ڵ�Ԫ����˱�־��λ���ʾ�˵�Ԫ���Խ������뽹�㣬��Ĭ�ϲ�ͣ��TAB����
    // ����־���ϱ�־���⡣
	#define		LDT_DEFAULT_NO_TABSTOP		(1 << 17)
    // �Ƿ�Ϊ��Ҫ�Ե���λ�û�ߴ����״���ڵ�Ԫ���繤������״̬���ȣ������ھ��д˱�־�ĵ�Ԫ��
    // ���ڴ��ڳߴ�ı������������ʱ�������Զ����͸�WU_SIZE_CHANGED��Ϣ��
    // ע�⣺��״���ڵ�Ԫ�����Ҫ�Զ��������������� CCS_TOP ���ڷ�������Ҫ�Զ��ײ�
    // ���������� CCS_BOTTOM ���ڷ��
	#define		LDT_BAR_SHAPE				(1 << 20)
	DWORD   m_dwState;

    ////////////////////////////////////////////
    // ���³�Աֻ����Ϊ���ڵ�Ԫ���˵�ʱ����Ч��

	DWORD m_dwUnitBmpID;		// ָ����֧�ֿ��еĵ�Ԫͼ����ԴID��ע�ⲻͬ�������ͼ����������0Ϊ�ޡ�
                                // �ߴ����Ϊ 24 X 24 ��������ɫΪ RGB (192, 192, 192) ��

	INT m_nEventCount;  // ����Ԫ���¼���Ŀ��
	PEVENT_INFO m_pEventBegin;	// ���屾��Ԫ�������¼���

	INT m_nPropertyCount;
	PUNIT_PROPERTY m_pPropertyBegin;

    // �����ṩ�����ڵ�Ԫ�����нӿڡ�
	PFN_GET_INTERFACE m_pfnGetInterface;

    ////////////////////////////////////////////
    // ���³�Աֻ���ڲ�Ϊ���ڵ�Ԫ���˵�ʱ����Ч��

	// �������������ӳ�Ա����Ŀ����Ϊ0������Ϊ���ڡ��˵���Ԫ���˱���ֵ��Ϊ0��
	INT	m_nElementCount;
	PLIB_DATA_TYPE_ELEMENT m_pElementBegin;  // ָ���ӳ�Ա������׵�ַ��
};
typedef LIB_DATA_TYPE_INFO* PLIB_DATA_TYPE_INFO;

/*////////////////////////////////////////////*/

struct LIB_CONST_INFO  // �ⳣ�����ݽṹ
{
	LPTSTR	m_szName;
	LPTSTR	m_szEGName;
	LPTSTR	m_szExplain;

	SHORT	m_shtReserved;  // ����Ϊ 1 ��

	#define	CT_NULL			0
	#define	CT_NUM			1	// sample: 3.1415926
	#define	CT_BOOL			2	// sample: 1
	#define	CT_TEXT			3	// sample: "abc"
	SHORT	m_shtType;

	LPTSTR	m_szText;		// CT_TEXT
	DOUBLE	m_dbValue;		// CT_NUM��CT_BOOL
};
typedef LIB_CONST_INFO* PLIB_CONST_INFO;

//////////////////////////////////////////// �������ݽṹ��

typedef struct
{
    DWORD m_dwFormID;
    DWORD m_dwUnitID;
}
MUNIT, *PMUNIT;

#pragma pack (push, old_value)   // ����VC++�������ṹ�����ֽ�����
#pragma pack (1)    // ����Ϊ��һ�ֽڶ��롣

struct MDATA_INF
{
    union
    {
        // ע�⵱��Ӧ��������AS_RECEIVE_VAR��AS_RECEIVE_VAR_ARRAY��AS_RECEIVE_VAR_OR_ARRAY
        // ��־����ʱ��ʹ������ĵڶ����֡�

        // ��һ���֡�
	    BYTE	      m_byte;         // SDT_BYTE �������͵����ݣ���ͬ��
	    SHORT	      m_short;        // SDT_SHORT
	    INT		      m_int;          // SDT_INT
	    INT64	      m_int64;        // SDT_INT64
	    FLOAT	      m_float;        // SDT_FLOAT
	    DOUBLE	      m_double;       // SDT_DOUBLE
        DATE          m_date;         // SDT_DATE_TIME
        BOOL          m_bool;         // SDT_BOOL

        char*         m_pText;        // SDT_TEXT������ϵͳԤ������ʹ�ǿ��ı�����ָ��ֵҲ����ΪNULL���Ա��ڴ���
                                      // ָ����ָ�����ݵĸ�ʽ��ǰ���������
                                      // !!!Ϊ�˱����޸ĵ�������(m_pText�п��ܻ�ָ���׳�����������)��
                                      // �����ݣ�ֻ�ɶ�ȡ�����ɸ������е����ݣ���ͬ��

        LPBYTE        m_pBin;         // SDT_BIN������ϵͳԤ������ʹ�ǿ��ֽڼ�����ָ��ֵҲ����ΪNULL���Ա��ڴ���
                                      // ָ����ָ�����ݵĸ�ʽ��ǰ���������
                                      // !!!ֻ�ɶ�ȡ�����ɸ������е����ݡ�

        DWORD         m_dwSubCodeAdr; // SDT_SUB_PTR��Ϊ�ӳ�������ַָ�롣
        MUNIT         m_unit;         // ���ڵ�Ԫ���˵��������͵����ݡ�

        void*         m_pCompoundData;// ����������������ָ�룬ָ����ָ�����ݵĸ�ʽ��ǰ���������
                                      // !!! ֻ�ɶ�ȡ�����ɸ������е����ݡ�

        void*         m_pAryData;     // ��������ָ�룬ָ����ָ�����ݵĸ�ʽ��ǰ���������
                                      // ע�����Ϊ�ı����ֽڼ����飬���Ա����ָ�����ΪNULL��
                                      // !!! ֻ�ɶ�ȡ�����ɸ������е����ݡ�

        // �ڶ����֡�
        // Ϊָ�������ַ��ָ�룬������������AS_RECEIVE_VAR��AS_RECEIVE_VAR_ARRAY��
        // AS_RECEIVE_VAR_OR_ARRAY��־ʱ�ű�ʹ�á�
        BYTE*	m_pByte;            // SDT_BYTE �������ͱ����ĵ�ַ����ͬ��
	    SHORT*	m_pShort;           // SDT_SHORT
	    INT*	m_pInt;             // SDT_INT
	    INT64*	m_pInt64;           // SDT_INT64
	    FLOAT*	m_pFloat;           // SDT_FLOAT
	    DOUBLE*	m_pDouble;          // SDT_DOUBLE
        DATE*   m_pDate;            // SDT_DATE_TIME
        BOOL*   m_pBool;            // SDT_BOOL

        char**  m_ppText;           // SDT_TEXT��ע��*m_ppText����ΪNULL��������ı�����
                                    // д����ֵ֮ǰ�����ͷ�ǰֵ�����䣺NotifySys (NRS_MFREE, (DWORD)*m_ppText)��
                                    // !!!����ֱ�Ӹ���*m_ppText��ָ������ݣ�ֻ���ͷ�ԭָ���������NULL�����ı���
                                    // ��ʹ��NRS_MALLOC֪ͨ��������ڴ��ַָ�루��ͬ����

        LPBYTE* m_ppBin;            // SDT_BIN��ע��*m_ppBin����ΪNULL��������ֽڼ�����
                                    // д����ֵ֮ǰ�����ͷ�ǰֵ�����䣺NotifySys (NRS_MFREE, (DWORD)*m_ppBin)��
                                    // !!!����ֱ�Ӹ���*m_ppBin��ָ������ݣ�ֻ���ͷ�ԭָ���������NULL�����ֽڼ���
                                    // ����ָ�롣

        DWORD*  m_pdwSubCodeAdr;    // SDT_SUB_PTR���ӳ�������ַ������ַ��
        PMUNIT  m_pUnit;            // ���ڵ�Ԫ���˵��������ͱ�����ַ��

        void**  m_ppCompoundData;   // �����������ͱ�����ַ��
                                    // !!!ע��д����ֵ֮ǰ����ʹ��NRS_MFREE֪ͨ��һ�ͷ����г�Ա������SDT_TEXT��
                                    // SDT_BIN�������������ͳ�Ա����ԭ��ַָ�롣
                                    // !!!����ֱ�Ӹ���*m_ppCompoundData��ָ������ݣ�ֻ���ͷ�ԭָ�����������ָ�롣

        void**  m_ppAryData;        // �������ݱ�����ַ��ע�⣺
                                    // 1��д����ֵ֮ǰ�����ͷ�ԭֵ�����䣺NotifySys (NRS_FREE_ARY,
                                    //    m_dtDataType, (DWORD)*m_ppAryData)��ע�⣺������ֻ������
                                    //    m_dtDataTypeΪϵͳ������������ʱ����������Ϊ�����������ͣ�
                                    //    ��������䶨����Ϣ��һ�ͷš�
                                    // 2�����Ϊ�ı����ֽڼ����飬�����г�Ա������ָ�����ΪNULL��
                                    // !!!����ֱ�Ӹ���*m_ppAryData��ָ������ݣ�ֻ���ͷ�ԭָ�����������ָ�롣
    };

    // 1�����������ݲ�������ʱ������ò������� AS_RECEIVE_VAR_OR_ARRAY ��
    //    AS_RECEIVE_ALL_TYPE_DATA ��־����Ϊ�������ݣ��������־ DT_IS_ARY ��
    //    ��Ҳ�� DT_IS_ARY ��־��Ψһʹ�ó��ϡ�
    //    DT_IS_ARY �Ķ���Ϊ��
    //      #define	DT_IS_ARY   0x20000000
    // 2�����������ݲ�������ʱ�����Ϊ�հ����ݣ���Ϊ _SDT_NULL ��
    DATA_TYPE m_dtDataType;
};
typedef MDATA_INF* PMDATA_INF;
// !!! ASSERT (sizeof (MDATA_INF) == sizeof (DWORD) * 3);
// �ߴ������� sizeof (DWORD) * 3 ��

#pragma pack (pop, old_value)    // �ָ�VC++�������ṹ�����ֽ�����

//////////////////////////////////////////// ֪ͨ�����ݽṹ��

/*/////////////*/
// ֧�ֿ����֪ͨ�ױ༭����(IDE)�������л���(RUNTIME)����ֵ��

struct MDATA
{
	MDATA ()
	{
		m_pData = NULL;
		m_nDataSize = 0;
	}

	LPBYTE	m_pData;
	INT		m_nDataSize;
};
typedef MDATA* PMDATA;

struct EVENT_NOTIFY
{
	// ��¼�¼�����Դ
	DWORD	m_dwFormID;		// ����ITF_CREATE_UNIT�ӿ������ݹ�������������ID��dwWinFormID������
	DWORD	m_dwUnitID;		// ����ITF_CREATE_UNIT�ӿ������ݹ����Ĵ��ڵ�ԪID��dwUnitID������
	INT		m_nEventIndex;	//   �¼��������ڴ��ڵ�Ԫ������ϢLIB_DATA_TYPE_INFO��m_pPropertyBegin
                            // ��Ա�е�λ�ã�

	INT		m_nArgCount;		// ���¼������ݵĲ�����Ŀ����� 5 ����
	INT		m_nArgValue [5];	// ��¼������ֵ��SDT_BOOL �Ͳ���ֵΪ 1 �� 0��

    //!!! ע������������Ա��û�ж��巵��ֵ���¼�����Ч����ֵ����Ϊ����ֵ��
	BOOL	m_blHasReturnValue; // �û��¼������ӳ���������¼����Ƿ��ṩ�˷���ֵ��
	INT		m_nReturnValue; // �û��¼������ӳ���������¼���ķ���ֵ���߼�ֵ����ֵ 0���٣� �� 1���棩 ���ء�

    /////////////////////////////////////

	EVENT_NOTIFY (DWORD dwFormID, DWORD dwUnitID, INT nEventIndex)
	{
		m_dwFormID = dwFormID;
		m_dwUnitID = dwUnitID;
		m_nEventIndex = nEventIndex;

		m_nArgCount = 0;
		m_blHasReturnValue = FALSE;
		m_nReturnValue = 0;
	}
};
typedef EVENT_NOTIFY* PEVENT_NOTIFY;

/*///////////////////////*/

// NES_ ��Ϊ�����ױ༭����(IDE)�����֪ͨ��
#define NES_GET_MAIN_HWND			        1
	// ȡ�ױ༭���������ڵľ����������֧�ֿ��AddIn������ʹ�á�
#define	NES_RUN_FUNC				        2
	// ֪ͨ�ױ༭��������ָ���Ĺ��ܣ�����һ��BOOLֵ��
	// dwParam1Ϊ���ܺš�
	// dwParam2Ϊһ��˫DWORD����ָ��,�ֱ��ṩ���ܲ���1��2��

// NAS_ ��Ϊ�ȱ��ױ༭�����ֱ������л��������֪ͨ��
#define NAS_GET_LIB_DATA_TYPE_INFO          1002
    // ����ָ���ⶨ���������͵�PLIB_DATA_TYPE_INFO������Ϣָ�롣
    // dwParam1Ϊ����ȡ��Ϣ����������DATA_TYPE��
    // ���������������Ч���߲�Ϊ�ⶨ���������ͣ��򷵻�NULL�����򷵻�PLIB_DATA_TYPE_INFOָ�롣

// NRS_ ��Ϊ���ܱ������л��������֪ͨ��
#define NRS_UNIT_DESTROIED			        2000
	// ֪ͨϵͳָ���ĵ�Ԫ�Ѿ������١�
	// dwParam1ΪdwFormID
	// dwParam2ΪdwUnitID
#define NRS_CONVERT_NUM_TO_INT              2001
	// ת��������ֵ��ʽ��������
	// dwParam1Ϊ PMDATA_INF ָ�룬�� m_dtDataType ����Ϊ��ֵ�͡�
    // ����ת���������ֵ��
#define NRS_GET_CMD_LINE_STR			    2002
	// ȡ��ǰ�������ı�
	// �����������ı�ָ�룬�п���Ϊ�մ���
#define NRS_GET_EXE_PATH_STR                2003
	// ȡ��ǰִ���ļ�����Ŀ¼����
	// ���ص�ǰִ���ļ�����Ŀ¼�ı�ָ�롣
#define NRS_GET_EXE_NAME				    2004
	// ȡ��ǰִ���ļ�����
	// ���ص�ǰִ���ļ������ı�ָ�롣
#define NRS_GET_UNIT_PTR				    2006
	// ȡ��Ԫ����ָ��
	// dwParam1ΪWinForm��ID
	// dwParam2ΪWinUnit��ID
	// �ɹ�������Ч�ĵ�Ԫ����CWnd*ָ�룬ʧ�ܷ���NULL��
#define NRS_GET_AND_CHECK_UNIT_PTR			2007
	// ȡ��Ԫ����ָ��
	// dwParam1ΪWinForm��ID
	// dwParam2ΪWinUnit��ID
	// �ɹ�������Ч�ĵ�Ԫ����CWnd*ָ�룬ʧ���Զ���������ʱ���������˳�����
#define NRS_EVENT_NOTIFY				    2008
	// ֪ͨϵͳ�������¼���
	// dwParam1ΪPEVENT_NOTIFYָ�롣
	//   ������� 0 ����ʾ���¼��ѱ�ϵͳ�����������ʾϵͳ�Ѿ��ɹ����ݴ��¼����û�
	// �¼������ӳ���
#define NRS_STOP_PROCESS_EVENT_NOTIFY	    2009
	// ֪ͨϵͳ��ͣ�����¼�֪ͨ��
#define NRS_CONTINUE_PROCESS_EVENT_NOTIFY	2010
	// ֪ͨϵͳ���������¼�֪ͨ��
#define	NRS_DO_EVENTS			            2018
	// ֪ͨWindowsϵͳ�������������¼���
#define NRS_GET_UNIT_DATA_TYPE              2022
	// dwParam1ΪWinForm��ID
	// dwParam2ΪWinUnit��ID
	// �ɹ�������Ч�� DATA_TYPE ��ʧ�ܷ��� 0 ��
#define NRS_FREE_ARY                        2023
    // �ͷ�ָ���������ݡ�
    // dwParam1Ϊ�����ݵ�DATA_TYPE��ֻ��Ϊϵͳ�����������͡�
    // dwParam2Ϊָ����������ݵ�ָ�롣
#define NRS_MALLOC                          2024
    // ����ָ���ռ���ڴ棬�������׳��򽻻����ڴ涼����ʹ�ñ�֪ͨ���䡣
    //   dwParam1Ϊ�������ڴ��ֽ�����
    //   dwParam2��Ϊ0�����������ʧ�ܾ��Զ���������ʱ���˳�����
    // �粻Ϊ0�����������ʧ�ܾͷ���NULL��
    //   �����������ڴ���׵�ַ��
#define NRS_MFREE                           2025
    // �ͷ��ѷ����ָ���ڴ档
    // dwParam1Ϊ���ͷ��ڴ���׵�ַ��
#define NRS_MREALLOC                        2026
    // ���·����ڴ档
    //   dwParam1Ϊ�����·����ڴ�ߴ���׵�ַ��
    //   dwParam2Ϊ�����·�����ڴ��ֽ�����
    // ���������·����ڴ���׵�ַ��ʧ���Զ���������ʱ���˳�����
#define	NRS_RUNTIME_ERR			            2027
	// ֪ͨϵͳ�Ѿ���������ʱ����
	// dwParam1Ϊchar*ָ�룬˵�������ı���
#define	NRS_EXIT_PROGRAM                    2028
	// ֪ͨϵͳ�˳��û�����
	// dwParam1Ϊ�˳����룬�ô��뽫�����ص�����ϵͳ��
#define NRS_GET_PRG_TYPE                    2030
    // ���ص�ǰ�û���������ͣ�Ϊ2�����԰棩��3�������棩��

/*///////////////////////////////////////////////////////////////////*/
// �ױ༭����(IDE)�������л���(RUNTIME)����֪֧ͨ�ֿ����ֵ��
#define	NL_SYS_NOTIFY_FUNCTION		1
	//   ��֪֧�ֿ�֪ͨϵͳ�õĺ���ָ�룬��װ��֧�ֿ�ǰ֪ͨ�������ж�Σ�
	// ��֪ͨ��ֵӦ�ø���ǰ����֪ͨ��ֵ�������Է���ֵ��
	//   ��ɽ��˺���ָ���¼�����Ա�����Ҫʱʹ����֪ͨ��Ϣ��ϵͳ��
	//   dwParam1: (PFN_NOTIFY_SYS)


/*///////////////////////////////////////////////////////////////////*/

#define NR_OK		0
#define NR_ERR		-1
typedef INT (WINAPI *PFN_NOTIFY_LIB) (INT nMsg, DWORD dwParam1, DWORD dwParam2);
	// �˺��������ױ༭����(IDE)�������л���(RUNTIME)֪֧ͨ�ֿ��й��¼���
typedef INT (WINAPI *PFN_NOTIFY_SYS) (INT nMsg, DWORD dwParam1, DWORD dwParam2);
	// �˺���������֪ͨ�ױ༭����(IDE)�������л���(RUNTIME)�й��¼���

/* ��������ͷ���ʵ�ֺ�����ԭ�͡�
   1�������� CDECL ���÷�ʽ��
   2��pRetData �����������ݣ�
   3��!!!���ָ����������������Ͳ�Ϊ _SDT_ALL ������
      ����� pRetData->m_dtDataType�����Ϊ _SDT_ALL ���������д��
   4��pArgInf �ṩ�������ݱ�����ָ��� MDATA_INF ��¼ÿ�������������Ŀ��ͬ�� nArgCount ��*/
typedef void (*PFN_EXECUTE_CMD) (PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf);
// ����֧�ֿ���ADDIN���ܵĺ���
typedef INT (WINAPI *PFN_RUN_ADDIN_FN) (INT nAddInFnIndex);
// ���������ṩ�ĳ���ģ�����ĺ���
typedef INT (WINAPI *PFN_SUPER_TEMPLATE) (INT nTemplateIndex);

////////////////////////////////////////////////////

#define		LIB_FORMAT_VER		20000101	// ���ʽ��

/*	!!! ע�⣺֧�ֿ��ļ����ĺ�׺����̶�Ϊ.FNx������xΪһ������ĸ��Ŀǰ������ĺ�׺�У�
	1����.fne����	���༭��Ϣ��������֧�ִ����֧�ֿ⣻
	2����.fnl����	���༭��Ϣ��������֧�ִ����֧�ֿ⣻
	3����.fnr����	�����༭��������Ϣ����������֧�ִ����֧�ֿ⣻
*/

typedef struct
{
	DWORD				m_dwLibFormatVer;
		// ���ʽ�ţ�Ӧ�õ���LIB_FORMAT_VER��

	LPTSTR				m_szGuid;
		// ��Ӧ�ڱ����ΨһGUID��������ΪNULL��գ���ͬ������к����汾�˴���Ӧ��ͬ��
        // ע��� GUID �ı�����ʹ��ר�ù������(���汾�ĵ�������guidgen.exe)���ɣ��Է�ֹ�����ظ���

	INT					m_nMajorVersion;	// ��������汾�ţ��������0��
	INT					m_nMinorVersion;	// ����Ĵΰ汾�š�

	INT					m_nBuildNumber;
		// �����汾�š�
		//   ���汾�Ž�����������ͬ��ʽ�汾�ŵ�ϵͳ�����Ʃ������޸��˼��� BUG��
		// ��ֵ��������ʽ�汾��ϵͳ��������κι��������û�ʹ�õİ汾�乹���汾
		// �Ŷ�Ӧ�ò�һ����
		//   ��ֵʱӦ��˳�������

	INT					m_nRqSysMajorVer;		// ����Ҫ������ϵͳ�����汾�ţ�ĿǰӦ��Ϊ 3 ��
	INT					m_nRqSysMinorVer;		// ����Ҫ������ϵͳ�Ĵΰ汾�ţ�ĿǰӦ��Ϊ 0 ��
	INT					m_nRqSysKrnlLibMajorVer;	// ����Ҫ��ϵͳ����֧�ֿ�����汾�ţ�ĿǰӦ��Ϊ 3 ��
	INT					m_nRqSysKrnlLibMinorVer;	// ����Ҫ��ϵͳ����֧�ֿ�Ĵΰ汾�ţ�ĿǰӦ��Ϊ 0 ��

	LPTSTR				m_szName;		// ����������ΪNULL��ա�
    // ��������
    #define LT_CHINESE  1
    #define LT_ENGLISH  2
	INT					m_nLanguage;	// ������֧�ֵ����ԣ�ĿǰӦ��Ϊ LT_CHINESE ��
	LPTSTR				m_szExplain;	// �йر������ϸ����

	#define		LBS_FUNC_NO_RUN_CODE		(1 << 2)
		// �����Ϊ�����⣬û�ж�Ӧ���ܵ�֧�ִ��룬��˲������С�
	#define		LBS_NO_EDIT_INFO			(1 << 3)
		// �������޹��༭�õ���Ϣ���༭��Ϣ��ҪΪ���������ơ������ַ����ȣ����޷���������IDE���ء�
	DWORD				m_dwState;

//////////////////  �йر������ߵ���Ϣ��
	LPTSTR				m_szAuthor;
	LPTSTR				m_szZipCode;
	LPTSTR				m_szAddress;
	LPTSTR				m_szPhone;
	LPTSTR				m_szFax;
	LPTSTR				m_szEmail;
	LPTSTR				m_szHomePage;
	LPTSTR				m_szOther;

//////////////////
	INT                 m_nDataTypeCount;	// �������Զ����������͵���Ŀ���������m_pDataType��ָ�������Ա����Ŀ��
	PLIB_DATA_TYPE_INFO m_pDataType;		// �����������Զ����������͵Ķ�����Ϣ��

	INT					m_nCategoryCount;	// ȫ�����������Ŀ�������ͬ������m_szzCategory��Ա��ʵ���ṩ����Ŀ��
	LPTSTR				m_szzCategory;		// ȫ���������˵����ÿ��Ϊһ�ַ�����ǰ��λ���ֱ�ʾͼ�������ţ���1��ʼ��0��ʾ�ޣ���
                                            // ��һ���ֵΪָ��֧�ֿ�����Ϊ"LIB_BITMAP"��BITMAP��Դ��ĳһ����16X13λͼ��������

	INT					m_nCmdCount;        // �������ṩ����������(ȫ��������󷽷�)����Ŀ(������Ϊ0)��
	PCMD_INFO			m_pBeginCmdInfo;	// ָ��������������Ķ�����Ϣ����(��m_nCmdCountΪ0,��ΪNULL)��
	PFN_EXECUTE_CMD*    m_pCmdsFunc;		// ָ��ÿ�������ʵ�ִ����׵�ַ��(��m_nCmdCountΪ0,��ΪNULL)��

	PFN_RUN_ADDIN_FN	m_pfnRunAddInFn;	// ��ΪNULL������Ϊ������IDE�ṩ���ӹ��ܡ�
	//     �й�AddIn���ܵ�˵���������ַ���˵��һ�����ܡ���һ��Ϊ��������
	// ����20�ַ������ڶ���Ϊ������ϸ���ܣ���60�ַ���������������մ�������
	LPTSTR				m_szzAddInFnInfo;

	PFN_NOTIFY_LIB		m_pfnNotify;		// ����ΪNULL���ṩ��������������IDE�����л���֪ͨ��Ϣ�ĺ�����

    // ����ģ����ʱ�������á�
	PFN_SUPER_TEMPLATE	m_pfnSuperTemplate;	// ΪNULL
	LPTSTR m_szzSuperTemplateInfo;	// ΪNULL

	// ���ⶨ������г�����
	INT	m_nLibConstCount;   // ������Ŀ��
	PLIB_CONST_INFO m_pLibConst;    // ָ�����������顣

	LPTSTR m_szzDependFiles;	// ��ΪNULL
	    // ����������������Ҫ�����������ļ�����������װ���ʱ�����Զ�������Щ�ļ���
}
LIB_INFO, *PLIB_INFO;

/*////////////////////////////////////////////*/

#define	FUNCNAME_GET_LIB_INFO		"GetNewInf"     // ȡ��֧�ֿ��PLIB_INFOָ��������������
typedef PLIB_INFO (WINAPI *PFN_GET_LIB_INFO) ();	// GetNewInf�ĺ���ԭ��
typedef INT (*PFN_ADD_IN_FUNC) ();  // m_pfnRunAddInFn�ĺ���ԭ��

/*////////////////////////////////////////////*/

#define LIB_BMP_RESOURCE	"LIB_BITMAP"	    // ֧�ֿ����ṩ��ͼ����Դ������
#define LIB_BMP_CX			16					// ÿһͼ����Դ�Ŀ��
#define LIB_BMP_CY			13					// ÿһͼ����Դ�ĸ߶�
#define LIB_BMP_BKCOLOR		RGB(255, 255, 255)	// ͼ����Դ�ĵ�ɫ

//////////////////////////// ����ʱ��ʹ�õĺ�

#define	WU_GET_WND_PTR			(WM_APP + 2)	// ����֧�ִ��ڵ�Ԫ�¼�������
#define	WU_SIZE_CHANGED			(WM_APP + 3)	// �����ڴ��ڳߴ�ı��֪ͨ������״���ڵ�Ԫ��
#define	WU_PARENT_RELAYOUT_BAR	(WM_APP + 4)	//   ����֪ͨ���㴰�����²������е� bar ��Ԫ��
                                                // ͨ���� bar ��Ԫ�ı�������ߴ��ʹ�á�

#endif
