#pragma once
#define SAMPLE_HOLD_LOW_MILLIS 18
#define DEFAULT_MAX_RETRIES 20

#ifdef DLLEVENT_EXPORTS 
#undef DLLEVENT_EXPORTS
#define DLLEVENT_EXPORTS __declspec(dllexport)  
#else   
#define DLLEVENT_EXPORTS __declspec(dllimport)
#endif


namespace WiegnerCardReader {
	public value struct WiegnerReading {
		byte currentRead;
		bool TimedOut;
		bool isValid;
		int retryCount;
	};

	public delegate void RecieveData(WiegnerReading);

	public interface class IWiegnerReader
	{
		void GetReadingAsync();
	};

	public ref class WiegnerReader sealed : IWiegnerReader
	{
	public:
		WiegnerReader(Windows::Devices::Gpio::GpioPin^ d0, Windows::Devices::Gpio::GpioPin^ d1);
		event RecieveData ^ RecievedData;
		virtual ~WiegnerReader();
		virtual void GetReadingAsync();
		void InternalGetReading();

	private:
		Windows::Devices::Gpio::GpioPin^ _D0;
		Windows::Devices::Gpio::GpioPin^ _D1;

	};
}