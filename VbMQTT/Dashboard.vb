Public Class Dashboard
    Private Sub Button1_Click(sender As Object, e As EventArgs)
        Me.Close()
    End Sub

    Private Sub ToolStripButton1_Click(sender As Object, e As EventArgs)
        Me.WindowState = FormWindowState.Minimized

    End Sub

    Private Sub Dashboard_Load(sender As Object, e As EventArgs) Handles MyBase.Load
        SetStyle(ControlStyles.OptimizedDoubleBuffer, True)
    End Sub
End Class