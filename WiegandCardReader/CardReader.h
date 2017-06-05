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
	public value struct WiegnerInit {
		int D0;
		int D1;
		int LED;
		int BUZZER;
		int WG34;
		int DOOR;
		bool UseWG34 = false;
	};

	public value struct WiegnerReading {
		int64 currentData;
		bool isValid;
		int LED;
		int BUZZER;
		int WG34;
		int DOOR;
		bool UseWG34 = false;
	};

	public delegate void RecieveData(WiegnerReading);

	public interface class IWiegnerReader
	{
		void GetReadingAsync();
	};

	public ref class WiegnerReader sealed : IWiegnerReader
	{
	public:
		WiegnerReader(WiegnerInit);
		event RecieveData ^ RecievedData;
		virtual ~WiegnerReader();
		virtual void GetReadingAsync();

	private:
		Windows::Devices::Gpio::GpioPin^ _D0;
		Windows::Devices::Gpio::GpioPin^ _D1;
		int _BUZZER;
		int _LED;
		int _WG34;
		int _DOOR;
	};
}