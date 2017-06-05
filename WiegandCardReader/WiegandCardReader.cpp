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
using namespace WiegandCardReader;

_Use_decl_annotations_


WiegandReader::WiegandReader(WiegandInit init)
{
	// ***
	// *** Set Drive Mode to Input
	// ***
	this->_D0 = GpioController::GetDefault()->OpenPin(init.D0, GpioSharingMode::Exclusive);
	this->_D1 = GpioController::GetDefault()->OpenPin(init.D0, GpioSharingMode::Exclusive);
	this->_D0->SetDriveMode(GpioPinDriveMode::Input);
	this->_D1->SetDriveMode(GpioPinDriveMode::Input);

	// ***
	// *** Save the Pins
	// ***
	this->_BUZZER = init.BUZZER;
	this->_LED = init.LED;
	this->_WG34 = init.WG34;
	this->_DOOR = init.DOOR;
}

WiegandReader::~WiegandReader() {
	this->_D0 = nullptr;
	this->_D1 = nullptr;
}

void WiegandReader::GetReadingAsync()
{
	create_async([this]
	{
		bool okToRun = true;
		WiegandReading returnValue;
		returnValue.BUZZER = this->_BUZZER;
		returnValue.DOOR = this->_DOOR;
		returnValue.LED = this->_LED;
		while (okToRun) {
			// here is where the reading magic happens and when a read is complete we return an object that is read so the event can fire should be able to new up as many of these as ports are available

			// trigger the data recieved event
			RecievedData(returnValue);
		}
	});
}
