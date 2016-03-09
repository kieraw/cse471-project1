#include "stdafx.h"
#include "SubtractiveInstrument.h"
#include "Notes.h"

CSubtractiveInstrument::CSubtractiveInstrument()
{
	m_duration = 0.1;
}


CSubtractiveInstrument::~CSubtractiveInstrument()
{
}
CSubtractiveInstrument::CSubtractiveInstrument(double bpm)
{
	m_duration = 0.1;
	m_bpm = bpm;
}
void CSubtractiveInstrument::SetNote(CNote *note)
{
	// Get a list of all attribute nodes and the
	// length of that list
	CComPtr<IXMLDOMNamedNodeMap> attributes;
	note->Node()->get_attributes(&attributes);
	long len;
	attributes->get_length(&len);

	// Loop over the list of attributes
	for (int i = 0; i<len; i++)
	{
		// Get attribute i
		CComPtr<IXMLDOMNode> attrib;
		attributes->get_item(i, &attrib);

		// Get the name of the attribute
		CComBSTR name;
		attrib->get_nodeName(&name);

		// Get the value of the attribute.  A CComVariant is a variable
		// that can have any type. It loads the attribute value as a
		// string (UNICODE), but we can then change it to an integer 
		// (VT_I4) or double (VT_R8) using the ChangeType function 
		// and then read its integer or double value from a member variable.
		CComVariant value;
		attrib->get_nodeValue(&value);

		if (name == "duration")
		{
			value.ChangeType(VT_R8);
			SetDuration(value.dblVal * (60.0 / m_bpm));
		}

		else if (name == "note")
		{
			SetFreq(NoteToFrequency(value.bstrVal));
		}
		//Set what type of wave it is according to the xml
		else if (name == "wavetype")
		{
			if ((wstring)value.bstrVal == L"Sawtooth"){
				m_wave_type = L"Sawtooth";
				SetWaveType(L"Sawtooth");
			}
			else if ((wstring)value.bstrVal == L"Square"){
				m_wave_type = L"Square";
				SetWaveType(L"Square");
			}
			else if ((wstring)value.bstrVal == L"Triangle"){
				m_wave_type = L"Triangle";
				SetWaveType(L"Triangle");
			}
		}
	}
	
}

void CSubtractiveInstrument::Start()
{
	// set the sample rate of the wave
	mSubtractiveWave.SetSampleRate(GetSampleRate());
	mSubtractiveWave.Start();
	m_time = 0;
}
bool CSubtractiveInstrument::Generate()
{
	return false;
}


