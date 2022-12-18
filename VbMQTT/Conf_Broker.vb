Imports uPLibrary.Networking.M2Mqtt
Imports uPLibrary.Networking.M2Mqtt.Messages
Imports System.Text
Imports System.Threading
Imports System.Windows.Forms.VisualStyles.VisualStyleElement



Public Class Conf_Broker

    Dim client As MqttClient
    Dim Msg As StringBuilder = New StringBuilder(4096)
    Private Sub ToolStripButton1_Click(sender As Object, e As EventArgs)
        Me.WindowState = FormWindowState.Minimized
    End Sub

    Private Sub Conf_Broker_Load(sender As Object, e As EventArgs) Handles MyBase.Load

    End Sub

    Private Sub Button1_Click(sender As Object, e As EventArgs) Handles Button1.Click
        If (TextBox1.Text.Length <> 0) Then
            Try
                client = New MqttClient(TextBox1.Text)

                Dim clientId As String = Guid.NewGuid().ToString()
                ' AddHandler Client.MqttMsgPublishReceived, AddressOf Client_MqttMsgPublishReceived
                '  AddHandler Client.ConnectionClosed, AddressOf Client_Disconnect

                client.Connect(clientId)

                If client.IsConnected Then
                    ' ComboBox2.SelectedIndex = 0
                    ToolStripStatusLabel2.Text = TextBox1.Text
                    ToolStripStatusLabel2.ForeColor = Color.White
                    ToolStripStatusLabel2.BackColor = Color.DarkGreen
                Else
                    ToolStripStatusLabel2.Text = "Desconectado"
                    ToolStripStatusLabel2.ForeColor = Color.White
                    ToolStripStatusLabel2.BackColor = Color.DarkRed
                End If

            Catch ex As Exception

                ToolStripStatusLabel2.Text = ex.Message()
                ToolStripStatusLabel2.ForeColor = Color.White
                ToolStripStatusLabel2.BackColor = Color.DarkRed
                ' MsgBox(ex.Message(), MsgBoxStyle.Critical)
            End Try
        Else
            ToolStripStatusLabel2.Text = "Por favor Ingrese un broker Válido "

        End If
    End Sub

    Private Sub Client_MqttMsgPublishReceived(ByVal sender As Object, ByVal e As MqttMsgPublishEventArgs)
        Msg.AppendLine()
        Msg.Append("[" + TimeOfDay.ToString("h:mm:ss tt") + "] Topic: " + e.Topic.ToString() + ", Len: " + e.Message.Length.ToString() + ", Qos: " + e.QosLevel.ToString())
        Msg.AppendLine()
        Msg.Append("Msg : " + Encoding.Default.GetString(e.Message))
        Msg.AppendLine()

        ' SetText(Msg.ToString)

    End Sub

    Private Sub Button4_Click(sender As Object, e As EventArgs) Handles Button4.Click
        If (client IsNot Nothing AndAlso client.IsConnected()) Then
            client.Disconnect()
        Else
            ToolStripStatusLabel2.Text = "Error"
            ToolStripStatusLabel2.ForeColor = Color.White
            ToolStripStatusLabel2.BackColor = Color.DarkRed
        End If
    End Sub








    Public Function GenerateCode()
        Dim strInputString = "1234567890abcdefghijklmnopqrstuvwxyz"

        Dim intLength = Len(strInputString)

        Dim intNameLength = 10

        Randomize()

        Dim strName = ""

        For intStep = 1 To intNameLength
            Dim intRnd = Int((intLength * Rnd()) + 1)

            strName = strName & Mid(strInputString, intRnd, 1)
        Next

        GenerateCode = strName
    End Function



    Private Sub Button2_Click(sender As Object, e As EventArgs)
        SerialPort1.Close()

    End Sub

    Private Sub Button6_Click(sender As Object, e As EventArgs)

    End Sub
End Class