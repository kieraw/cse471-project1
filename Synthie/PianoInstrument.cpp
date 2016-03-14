#include "stdafx.h"
#include "PianoInstrument.h"

using namespace std;

CPianoInstrument::CPianoInstrument()
{
	m_attack = 0.05;
	m_release = 0.26;
	m_volume = 1.0;
	m_duration = 1.0;
	m_pedal = false;
}


CPianoInstrument::~CPianoInstrument()
{
}


void CPianoInstrument::Start(){
	m_wavePlayer.SetSampleRate(GetSampleRate());
	m_wavePlayer.Start();
}


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
		else if (name == "duration")
		{
			value.ChangeType(VT_R8);
			//Set the duration of the note to be the input duration plus the ramp down time after 
			//the note has been released
			SetDuration(value.dblVal + m_release);
		}
		
	}

	if (!m_pedal){
		ChangeDuration();
	}

	Envelope();
	this->GetPlayer()->SetSamples(&m_wave[0], (int)m_wave.size());
}


/* Load the file and create the initial wave table of the note */
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

/* Change the duration of the note to be what is supplied in the score*/
void CPianoInstrument::ChangeDuration()
{
	vector<short> changed_wave;
	double m_time = 0.0;
	int i = 0;

	if (m_duration == 0)
	{
		return;
	}

	//Create a new wave with the correct number of frames (duration) of the note
	while (m_time < m_duration)
	{
		changed_wave.push_back(m_wave[i]);

		i++;
		m_time += 1 / 44100.;

		if (i > m_wave.size() - 1)
		{
			i = 0;
		}
	}

	//Save the changed wave back into the original wave
	m_wave = changed_wave;
}



/* Function to control the attack/release periods of the note */
void CPianoInstrument::Envelope()
{
	double output;
	double m_ramp;
	double m_time = 0.0;
	double m_duration = m_wave.size() / 44100.;

	for (int i = 0; i < m_wave.size(); i++, m_time += 1 / 44100.)
	{
		if (m_time < m_attack)
		{
			m_ramp = (m_time / m_attack);
		}
		if (m_time >(m_duration - m_release))
		{
			m_ramp = (m_duration - m_time) / m_release;
		}

		output = m_wave[i] * m_ramp * m_volume;
		m_wave[i] = short(output);
	}
}
