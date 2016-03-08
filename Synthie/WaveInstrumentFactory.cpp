#include "StdAfx.h"
#include "WaveInstrumentFactory.h"
#include <cmath>

CWaveInstrumentFactory::CWaveInstrumentFactory(void)
{
	for (double time = 0; time<2; time += 1. / 44100.)
	{
		m_wave.push_back(short(3267 * sin(2 * 3.1415 * 1000 * time)));
	}
}

CWaveInstrumentFactory::~CWaveInstrumentFactory(void)
{
}


CWaveInstrument *CWaveInstrumentFactory::CreateInstrument()
{
	CWaveInstrument *instrument = new CWaveInstrument();
	instrument->GetPlayer()->SetSamples(&m_wave[0], (int)m_wave.size());

	return instrument;
}

void CWaveInstrumentFactory::SetNote(CNote *note)
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
		}

		else if (name == "file")
		{
			value.ChangeType(VT_BSTR);
			char filename[100];
			wcstombs(filename, value.bstrVal,100);
			LoadFile(filename);
		}
		else if (name == "pitch")
		{
			//ChangePitch();
		}
		else if (name == "glissando")
		{
			//Glissando();
		}
	}

}


bool CWaveInstrumentFactory::LoadFile(const char *filename)
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

	m_file.Close();
	return true;
}

void CWaveInstrumentFactory::ChangePitch(double rate)
{
	double sample = 0.0;

	double	inbetween = fmod(sample, 1);
	short output = (1. - inbetween) * m_wave[int(sample)] + inbetween * m_wave[int(sample) + 1];

	sample += rate;
}

void CWaveInstrumentFactory::Glissando(double rate)
{

}