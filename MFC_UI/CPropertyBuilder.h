//////////////////////////////////////////////////////////////////////////
/// Auto set and get
///
/// example:
///
/// CPROPERTY_BUILD(int,Flag)
/// int m_Flag;
/// void SetFlag(int v);
/// int GetFlag();
//////////////////////////////////////////////////////////////////////////

#ifndef CPropertyBuilder_h__
#define CPropertyBuilder_h__

#define CPROPERTY_BUILD(type,Name,classType)\
	public:\
		type m_##Name;\
		inline classType Set##Name(type v){\
			m_##Name = v;\
			return this;\
				};\
		inline type Get##Name(){\
			return m_##Name;\
				};
#endif // CPropertyBuilder_h__
