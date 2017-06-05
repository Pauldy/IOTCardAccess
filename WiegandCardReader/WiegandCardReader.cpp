#include "pch.h"
#include "WiegandCardReader.h"
#include <ppltasks.h>
#include <CardReader.h>

using namespace concurrency;
using namespace std;
using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::System::Threading;
using namespace Windows::Devices::Gpio;
using namespace WiegnerCardReader;

_Use_decl_annotations_


WiegnerReader::WiegnerReader(Windows::Devices::Gpio::GpioPin^ D0, Windows::Devices::Gpio::GpioPin^ D1)
{
	// ***
	// *** Set Drive Mode to Input
	// ***
	D0->SetDriveMode(Windows::Devices::Gpio::GpioPinDriveMode::Input);
	D1->SetDriveMode(Windows::Devices::Gpio::GpioPinDriveMode::Input);
	// ***
	// *** Save the Pin
	// ***
	this->_D0 = D0;
	this->_D1 = D1;
}

WiegnerReader::~WiegnerReader() {
	this->_D0 = nullptr;
	this->_D1 = nullptr;
}

void WiegnerReader::GetReadingAsync()
{
	create_async([this]
	{
		bool okToRun = true;
		while(okToRun)
			this->InternalGetReading();
	});
}

void WiegnerReader::InternalGetReading()
{
	WiegnerReading returnValue;
	 // here is where the reading magic happens and when a read is complete we return an object that is read so the event can fire should be able to new up as many of these as ports are available

	// trigger the data recieved event
	RecievedData(returnValue);
}
