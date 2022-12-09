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
        GetSerialPortNames()
        TopicosAleatorios()
        ComboBox3.DropDownStyle = ComboBoxStyle.DropDownList
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

    Sub GetSerialPortNames()

        ' muestra COM ports disponibles.
        Dim l As Integer
        Dim ncom As String
        Try
            ComboBox3.Items.Clear()
            For Each sp As String In My.Computer.Ports.SerialPortNames
                l = sp.Length

                If ((sp(l - 1) >= "0") And (sp(l - 1) <= "9")) Then
                    ComboBox3.Items.Add(sp)
                Else
                    'hay una letra al final del COM
                    ncom = sp.Substring(0, l - 1)
                    ComboBox3.Items.Add(ncom)
                End If
            Next
            If ComboBox3.Items.Count >= 1 Then
                ComboBox3.Text = ComboBox3.Items(0)
            Else
                ComboBox3.Text = ""
            End If
        Catch ex As Exception

        End Try

    End Sub

    Sub Setup_Puerto_Serie()

        Try
            With SerialPort1
                If .IsOpen Then
                    .Close()

                End If

                .PortName = ComboBox3.Text
                .BaudRate = 9600
                .DataBits = 8
                .StopBits = IO.Ports.StopBits.One
                .Parity = IO.Ports.Parity.None
                .DtrEnable = False
                .Handshake = IO.Ports.Handshake.None
                .ReadBufferSize = 2048
                .WriteBufferSize = 1024

                .WriteTimeout = 500
                .Encoding = System.Text.Encoding.Default

                .Open() ' ABRE EL PUERTO SERIE

            End With

        Catch ex As Exception
            MsgBox("Error al abrir el puerto serial: " & ex.Message, MsgBoxStyle.Critical)
        End Try
    End Sub

    Private Sub Button3_Click(sender As Object, e As EventArgs) Handles Button3.Click
        Try

            Setup_Puerto_Serie()

        Catch ex As Exception
            MsgBox("Error al abrir el puerto serial: " & ex.Message, MsgBoxStyle.Critical)
        End Try
    End Sub

    Private Sub Button5_Click(sender As Object, e As EventArgs) Handles Button5.Click
        TopicosAleatorios()
        MsgBox("Nuevos tópicos generados", MsgBoxStyle.Information)
    End Sub


    Sub TopicosAleatorios()
        Dim aleatorio As String = GenerateCode()
        TextBox4.Text = aleatorio + "/Zona1" + "/Temperatura"
        TextBox3.Text = aleatorio + "/Zona1" + "/Humedad"

        TextBox5.Text = aleatorio + "/Zona2" + "/Temperatura"
        TextBox2.Text = aleatorio + "/Zona2" + "/Humedad"

        TextBox9.Text = aleatorio + "/Actuador/" + "AC1"
        TextBox8.Text = aleatorio + "/Actuador/" + "AC2"

        ' 
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

    Private Sub Timer1_Tick(sender As Object, e As EventArgs) Handles Timer1.Tick
        If SerialPort1.IsOpen Then
            Label12.Text = "Conectado"
            Label12.ForeColor = Color.White
            Label12.BackColor = Color.DarkGreen
        Else

            Label12.Text = "Desconectado"
            Label12.ForeColor = Color.White
            Label12.BackColor = Color.DarkRed
        End If
    End Sub

    Private Sub Button2_Click(sender As Object, e As EventArgs) Handles Button2.Click
        SerialPort1.Close()

    End Sub
End Class