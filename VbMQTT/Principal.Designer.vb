<Global.Microsoft.VisualBasic.CompilerServices.DesignerGenerated()> _
Partial Class Principal
    Inherits System.Windows.Forms.Form

    'Form reemplaza a Dispose para limpiar la lista de componentes.
    <System.Diagnostics.DebuggerNonUserCode()> _
    Protected Overrides Sub Dispose(ByVal disposing As Boolean)
        Try
            If disposing AndAlso components IsNot Nothing Then
                components.Dispose()
            End If
        Finally
            MyBase.Dispose(disposing)
        End Try
    End Sub

    'Requerido por el Diseñador de Windows Forms
    Private components As System.ComponentModel.IContainer

    'NOTA: el Diseñador de Windows Forms necesita el siguiente procedimiento
    'Se puede modificar usando el Diseñador de Windows Forms.  
    'No lo modifique con el editor de código.
    <System.Diagnostics.DebuggerStepThrough()> _
    Private Sub InitializeComponent()
        Me.components = New System.ComponentModel.Container()
        Dim resources As System.ComponentModel.ComponentResourceManager = New System.ComponentModel.ComponentResourceManager(GetType(Principal))
        Me.NotifyIcon1 = New System.Windows.Forms.NotifyIcon(Me.components)
        Me.ToolStrip1 = New System.Windows.Forms.ToolStrip()
        Me.ToolStripSplitButton2 = New System.Windows.Forms.ToolStripSplitButton()
        Me.HistoricosToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.GráficosToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.ReportesToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.ToolStripButton1 = New System.Windows.Forms.ToolStripButton()
        Me.StatusStrip1 = New System.Windows.Forms.StatusStrip()
        Me.ToolStripStatusLabel1 = New System.Windows.Forms.ToolStripStatusLabel()
        Me.LB_Internet = New System.Windows.Forms.ToolStripStatusLabel()
        Me.ToolStripStatusLabel3 = New System.Windows.Forms.ToolStripStatusLabel()
        Me.LB_Fecha = New System.Windows.Forms.ToolStripStatusLabel()
        Me.TimerValidacion = New System.Windows.Forms.Timer(Me.components)
        Me.ToolStripButton2 = New System.Windows.Forms.ToolStripButton()
        Me.ToolStrip1.SuspendLayout()
        Me.StatusStrip1.SuspendLayout()
        Me.SuspendLayout()
        '
        'NotifyIcon1
        '
        resources.ApplyResources(Me.NotifyIcon1, "NotifyIcon1")
        '
        'ToolStrip1
        '
        resources.ApplyResources(Me.ToolStrip1, "ToolStrip1")
        Me.ToolStrip1.BackColor = System.Drawing.Color.Black
        Me.ToolStrip1.Items.AddRange(New System.Windows.Forms.ToolStripItem() {Me.ToolStripButton2, Me.ToolStripSplitButton2, Me.ToolStripButton1})
        Me.ToolStrip1.Name = "ToolStrip1"
        '
        'ToolStripSplitButton2
        '
        resources.ApplyResources(Me.ToolStripSplitButton2, "ToolStripSplitButton2")
        Me.ToolStripSplitButton2.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image
        Me.ToolStripSplitButton2.DropDownItems.AddRange(New System.Windows.Forms.ToolStripItem() {Me.HistoricosToolStripMenuItem, Me.GráficosToolStripMenuItem, Me.ReportesToolStripMenuItem})
        Me.ToolStripSplitButton2.Name = "ToolStripSplitButton2"
        '
        'HistoricosToolStripMenuItem
        '
        resources.ApplyResources(Me.HistoricosToolStripMenuItem, "HistoricosToolStripMenuItem")
        Me.HistoricosToolStripMenuItem.Name = "HistoricosToolStripMenuItem"
        '
        'GráficosToolStripMenuItem
        '
        resources.ApplyResources(Me.GráficosToolStripMenuItem, "GráficosToolStripMenuItem")
        Me.GráficosToolStripMenuItem.Name = "GráficosToolStripMenuItem"
        '
        'ReportesToolStripMenuItem
        '
        resources.ApplyResources(Me.ReportesToolStripMenuItem, "ReportesToolStripMenuItem")
        Me.ReportesToolStripMenuItem.Name = "ReportesToolStripMenuItem"
        '
        'ToolStripButton1
        '
        resources.ApplyResources(Me.ToolStripButton1, "ToolStripButton1")
        Me.ToolStripButton1.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image
        Me.ToolStripButton1.Name = "ToolStripButton1"
        '
        'StatusStrip1
        '
        resources.ApplyResources(Me.StatusStrip1, "StatusStrip1")
        Me.StatusStrip1.BackColor = System.Drawing.Color.Black
        Me.StatusStrip1.Items.AddRange(New System.Windows.Forms.ToolStripItem() {Me.ToolStripStatusLabel1, Me.LB_Internet, Me.ToolStripStatusLabel3, Me.LB_Fecha})
        Me.StatusStrip1.Name = "StatusStrip1"
        '
        'ToolStripStatusLabel1
        '
        resources.ApplyResources(Me.ToolStripStatusLabel1, "ToolStripStatusLabel1")
        Me.ToolStripStatusLabel1.ForeColor = System.Drawing.SystemColors.ControlLightLight
        Me.ToolStripStatusLabel1.Name = "ToolStripStatusLabel1"
        '
        'LB_Internet
        '
        resources.ApplyResources(Me.LB_Internet, "LB_Internet")
        Me.LB_Internet.ForeColor = System.Drawing.SystemColors.ControlLightLight
        Me.LB_Internet.Name = "LB_Internet"
        '
        'ToolStripStatusLabel3
        '
        resources.ApplyResources(Me.ToolStripStatusLabel3, "ToolStripStatusLabel3")
        Me.ToolStripStatusLabel3.ForeColor = System.Drawing.SystemColors.ControlLightLight
        Me.ToolStripStatusLabel3.Name = "ToolStripStatusLabel3"
        '
        'LB_Fecha
        '
        resources.ApplyResources(Me.LB_Fecha, "LB_Fecha")
        Me.LB_Fecha.ForeColor = System.Drawing.SystemColors.ControlLightLight
        Me.LB_Fecha.Name = "LB_Fecha"
        '
        'TimerValidacion
        '
        Me.TimerValidacion.Enabled = True
        Me.TimerValidacion.Interval = 1000
        '
        'ToolStripButton2
        '
        resources.ApplyResources(Me.ToolStripButton2, "ToolStripButton2")
        Me.ToolStripButton2.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image
        Me.ToolStripButton2.Name = "ToolStripButton2"
        '
        'Principal
        '
        resources.ApplyResources(Me, "$this")
        Me.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font
        Me.BackColor = System.Drawing.SystemColors.ControlLightLight
        Me.Controls.Add(Me.StatusStrip1)
        Me.Controls.Add(Me.ToolStrip1)
        Me.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle
        Me.IsMdiContainer = True
        Me.Name = "Principal"
        Me.WindowState = System.Windows.Forms.FormWindowState.Maximized
        Me.ToolStrip1.ResumeLayout(False)
        Me.ToolStrip1.PerformLayout()
        Me.StatusStrip1.ResumeLayout(False)
        Me.StatusStrip1.PerformLayout()
        Me.ResumeLayout(False)
        Me.PerformLayout()

    End Sub

    Friend WithEvents NotifyIcon1 As NotifyIcon
    Friend WithEvents ToolStrip1 As ToolStrip
    Friend WithEvents StatusStrip1 As StatusStrip
    Friend WithEvents ToolStripStatusLabel1 As ToolStripStatusLabel
    Friend WithEvents LB_Internet As ToolStripStatusLabel
    Friend WithEvents ToolStripStatusLabel3 As ToolStripStatusLabel
    Friend WithEvents LB_Fecha As ToolStripStatusLabel
    Friend WithEvents TimerValidacion As Timer
    Friend WithEvents ToolStripSplitButton2 As ToolStripSplitButton
    Friend WithEvents HistoricosToolStripMenuItem As ToolStripMenuItem
    Friend WithEvents GráficosToolStripMenuItem As ToolStripMenuItem
    Friend WithEvents ReportesToolStripMenuItem As ToolStripMenuItem
    Friend WithEvents ToolStripButton1 As ToolStripButton
    Friend WithEvents ToolStripButton2 As ToolStripButton
End Class
