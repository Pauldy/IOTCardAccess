#pragma once
#define SAMPLE_HOLD_LOW_MILLIS 18
#define DEFAULT_MAX_RETRIES 20

namespace CardReader {
	namespace Wiegner {
		public value struct WiegnerReading {
			char* currentRead;
			bool TimedOut;
			bool isValid;
			int retryCount;
		};

		public interface class IWiegnerReader 
		{
			Windows::Foundation::IAsyncOperation<WiegnerReading>^ GetReadingAsync();
			Windows::Foundation::IAsyncOperation<WiegnerReading>^ GetReadingAsync(int maxRetries);
		};

		public ref class WiegnerCardReader sealed : IWiegnerReader
		{
		public:
			WiegnerCardReader(Windows::Devices::Gpio::GpioPin^ d0, Windows::Devices::Gpio::GpioPin^ d1);
			virtual ~WiegnerCardReader();

			virtual Windows::Foundation::IAsyncOperation<WiegnerReading>^ GetReadingAsync();
			virtual Windows::Foundation::IAsyncOperation<WiegnerReading>^ GetReadingAsync(int maxRetries);

		private:
			Windows::Devices::Gpio::GpioPin^ _D0;
			Windows::Devices::Gpio::GpioPin^ _D1;

			WiegnerReading InternalGetReading();
		};

	}
}