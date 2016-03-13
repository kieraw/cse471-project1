#include "stdafx.h"
#include "PianoInstrument.h"


CPianoInstrument::CPianoInstrument()
{
}


CPianoInstrument::~CPianoInstrument()
{
}


void CPianoInstrument::Start(){
	m_wavePlayer.SetSampleRate(GetSampleRate());
	m_wavePlayer.Start();
}


//void CPianoInstrument::SetNote(CNote *note)
void CPianoInstrument::SetNote(CNote *note)
{
	// Get a list of all attribute nodes and the
	// length of that list
	CComPtr<IXMLDOMNamedNodeMap> attributes;
	note->Node()->get_attributes(&attributes);
	long len;
	attributes->get_length(&len);

	// Loop over the list of attributes
	for (int i = 0; i < len; i++)
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

		if (name == "note")
		{
			value.ChangeType(VT_BSTR);
			char filename[100];
			wcstombs(filename, value.bstrVal, 100);
			LoadFile(filename);
		}
	}
}

bool CPianoInstrument::LoadFile(const char *filename)
{
	m_wave.clear();

	CDirSoundSource m_file;

	if (!m_file.Open(filename))
	{
		CString msg = L"Unable to open audio file: ";
		msg += filename;
		AfxMessageBox(msg);
		return false;
	}

	for (int i = 0; i<m_file.NumSampleFrames(); i++)
	{
		short frame[2];
		m_file.ReadFrame(frame);
		m_wave.push_back(frame[0]);
	}

	this->GetPlayer()->SetSamples(&m_wave[0], (int)m_wave.size());

	m_file.Close();
	return true;
}

bool CPianoInstrument::Generate()
{
	bool valid = m_wavePlayer.Generate();

	m_frame[0] = m_wavePlayer.Frame(0);
	m_frame[1] = m_frame[0];

	return valid;
}
