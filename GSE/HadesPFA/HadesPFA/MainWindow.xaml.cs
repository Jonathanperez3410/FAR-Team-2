using System;
using System.IO;
using System.Windows;
using Microsoft.Win32;

namespace HadesPFA
{
	/// <summary>
	/// Interaction logic for MainWindow.xaml
	/// </summary>
	public partial class MainWindow : Window
	{
		public MainWindow()
		{
			InitializeComponent();
		}

		void btnOpenFile_Click(object sender, RoutedEventArgs e)
		{
			OpenFileDialog openFileDialog = new OpenFileDialog
			{
				Filter = "KXR Flight Data (*.kxr)|*.kxr|All files (*.*)|*.*"
			};

			if (openFileDialog.ShowDialog() == true)
				txtEditor.Text = File.ReadAllText(openFileDialog.FileName);
		}
	}
}