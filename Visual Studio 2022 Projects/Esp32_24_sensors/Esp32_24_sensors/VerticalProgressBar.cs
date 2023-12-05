using System;
using System.Collections.Generic;
using System.Drawing;
using System.Drawing.Drawing2D;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Esp32_24_sensors
{
    internal class VerticalProgressBar : ProgressBar
    {
        public int Rotation { get; set; }
        public Border3DStyle Border3DStyle { get; set; }
        /*
        protected override CreateParams CreateParams
        {
            get
            {
                CreateParams orientation = base.CreateParams;
                orientation.Style |= 0x04;
                return orientation;
            }
        }
        */
        public VerticalProgressBar()
        {
            // Enable custom painting
            this.SetStyle(ControlStyles.UserPaint, true);
        }

        protected override void OnPaint(PaintEventArgs e)
        {
            // Call the base class method
            base.OnPaint(e);

            // Get the graphics object
            Graphics g = e.Graphics;

            // Save the original state of the graphics object
            GraphicsState state = g.Save();

            // Move the coordinate system to the center of the rectangle
            g.TranslateTransform(this.Width / 2, this.Height / 2);

            // Rotate the coordinate system by the rotation angle
            g.RotateTransform(this.Rotation);

            // Move the coordinate system back to the original position
            g.TranslateTransform(-this.Width / 2, -this.Height / 2);

            // Create a brush with the desired color
            Brush b = new SolidBrush(Color.DarkSlateBlue);

            // Calculate the percentage of progress
            float percent = (float)(this.Value - this.Minimum) / (float)(this.Maximum - this.Minimum);

            // Draw the rectangle with the brush
            g.FillRectangle(b, 0, 0, this.Width, this.Height * percent);

            // Restore the original state of the graphics object
            g.Restore(state);
        }

        protected override void OnPaintBackground(PaintEventArgs pevent)
        {
            // Call the base class method
            base.OnPaintBackground(pevent);

            // Get the graphics object
            Graphics g = pevent.Graphics;

            // Draw the border with the desired style
            ControlPaint.DrawBorder3D(g, this.ClientRectangle, this.Border3DStyle);
        }

    }
}
