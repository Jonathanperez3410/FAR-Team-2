package gui.j3d;

import gui.HadesOS;

import javax.media.j3d.*;
import java.util.Enumeration;

public class RocketBehavior extends Behavior
{
    private final TransformGroup tg;

    private double angleX;
    private double angleY;
    private double angleZ;

    public RocketBehavior(TransformGroup tg)
    {
        this.tg = tg;
        angleX = 0.0;
        angleY = 0.0;
        angleZ = 0.0;
    }

    @Override
    public void initialize()
    {
        this.wakeupOn(new WakeupOnActivation());
    }

    @Override
    public void processStimulus(Enumeration enumeration)
    {
        try { angleX = Double.parseDouble(HadesOS.dataPanel.getAngleX()); }
        catch (Exception ignored) {}

        try { angleY = Double.parseDouble(HadesOS.dataPanel.getAngleY()); }
        catch (Exception ignored) {}

        try { angleZ = Double.parseDouble(HadesOS.dataPanel.getAngleZ()); }
        catch (Exception ignored) {}

        Transform3D rotation = new Transform3D();
        Transform3D rotX = new Transform3D(); rotX.rotX(angleZ * Math.PI / 180);
        Transform3D rotY = new Transform3D(); rotY.rotY(angleX * Math.PI / 180);
        Transform3D rotZ = new Transform3D(); rotZ.rotZ(angleY * Math.PI / 180);

        rotation.mul(rotX); rotation.mul(rotY); rotation.mul(rotZ);
        tg.setTransform(rotation);

        this.wakeupOn(new WakeupOnElapsedFrames(0));
    }
}
