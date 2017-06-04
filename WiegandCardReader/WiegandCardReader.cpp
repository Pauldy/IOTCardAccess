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
using namespace CardReader::Wiegner;

_Use_decl_annotations_

WiegnerCardReader::WiegnerCardReader(Windows::Devices::Gpio::GpioPin^ D0, Windows::Devices::Gpio::GpioPin^ D1)
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

WiegnerCardReader::~WiegnerCardReader() {
	this->_D0 = nullptr;
	this->_D1 = nullptr;
}

Windows::Foundation::IAsyncOperation<WiegnerReading>^ WiegnerCardReader::GetReadingAsync()
{
	return this->GetReadingAsync(DEFAULT_MAX_RETRIES);
}

Windows::Foundation::IAsyncOperation<WiegnerReading>^ WiegnerCardReader::GetReadingAsync(int maxRetries)
{
	return create_async([this, maxRetries]
	{
		WiegnerReading returnValue;
		int i = 0;

		for (i; i < maxRetries; i++)
		{
			returnValue = this->InternalGetReading();

			if (returnValue.isValid)
			{
				break;
			}
		}

		returnValue.retryCount = i;

		return returnValue;
	});
}

WiegnerReading WiegnerCardReader::InternalGetReading()
{
	WiegnerReading returnValue;
	 // here is where the reading magic happens and whena  read is complete we return an object that is read so the event can fire should be able to new up as many of these as ports are available
}
