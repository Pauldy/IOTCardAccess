using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices.WindowsRuntime;
using System.Threading;
using System.Threading.Tasks;
using Windows.Devices.Enumeration;
using Windows.Devices.SerialCommunication;
using Windows.Foundation;
using Windows.Foundation.Collections;
using Windows.Storage.Streams;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Controls.Primitives;
using Windows.UI.Xaml.Data;
using Windows.UI.Xaml.Input;
using Windows.UI.Xaml.Media;
using Windows.UI.Xaml.Navigation;
using WiegandCardReader;
using Windows.Devices.Gpio;

// The Blank Page item template is documented at http://go.microsoft.com/fwlink/?LinkId=402352&clcid=0x409

namespace IOTCardAccess
{
    /// <summary>
    /// An empty page that can be used on its own or navigated to within a Frame.
    /// </summary>
    public sealed partial class MainPage : Page
    {

        public MainPage()
        {
            this.InitializeComponent();
            GpioPin D0 = GpioController.GetDefault().OpenPin(4, GpioSharingMode.Exclusive);
            GpioPin D1 = GpioController.GetDefault().OpenPin(5, GpioSharingMode.Exclusive);


            WiegandReader reader = new WiegandReader(new WiegandInit() { D0 = 4, D1 = 5, BUZZER = 6, DOOR = 7, LED = 8, WG34 = 9, UseWG34 = false });
            reader.RecievedData += Reader_RecievedData;
            reader.GetReadingAsync();
        }

        private void Reader_RecievedData(WiegandReading __param0)
        {
            // receive the data do lookup and open appropriate gate

        }
    }
}
