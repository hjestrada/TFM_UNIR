Imports System.Threading

Public Class Principal
    Private Sub TimerValidacion_Tick(sender As Object, e As EventArgs) Handles TimerValidacion.Tick
        LB_Fecha.Text = Now

        If My.Computer.Network.IsAvailable = True Then
            Try
                If My.Computer.Network.Ping("www.google.com", 10) Then
                    LB_Internet.Text = "Conectado"
                    LB_Internet.ForeColor = Color.White
                    LB_Internet.BackColor = Color.DarkGreen
                End If
            Catch ex As Exception
                LB_Internet.Text = "Sin Conexión"
                LB_Internet.ForeColor = Color.White
                LB_Internet.BackColor = Color.DarkRed

            End Try
        End If
    End Sub

    Private Sub Principal_Load(sender As Object, e As EventArgs) Handles MyBase.Load
        TimerValidacion.Start()
    End Sub

    Private Sub SalirToolStripMenuItem_Click(sender As Object, e As EventArgs) Handles SalirToolStripMenuItem.Click
        Me.Close()
    End Sub



    Private Sub ToolStripButton1_Click(sender As Object, e As EventArgs) Handles ToolStripButton1.Click
        Dashboard.MdiParent = Me
        Dashboard.Show()
    End Sub

    Private Sub ConfiguraciónBrokerToolStripMenuItem_Click(sender As Object, e As EventArgs) Handles ConfiguraciónBrokerToolStripMenuItem.Click
        Conf_Broker.MdiParent = Me
        Conf_Broker.Show()
    End Sub
End Class
