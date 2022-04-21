package gui.j3d;

import java.awt.*;

import com.sun.j3d.utils.universe.*;
import com.sun.j3d.utils.geometry.*;
import javax.media.j3d.*;
import javax.swing.*;

public class Rocket3D extends JPanel
{
    public Rocket3D()
    {
        setLayout(new BorderLayout());
        setPreferredSize(new Dimension(300, 300));

        GraphicsConfiguration config = SimpleUniverse.getPreferredConfiguration();
        Canvas3D canvas = new Canvas3D(config);
        SimpleUniverse universe = new SimpleUniverse(canvas);
        BranchGroup cubeRoot = new BranchGroup();

        TransformGroup cubeRotate = new TransformGroup();
        cubeRotate.setCapability(TransformGroup.ALLOW_TRANSFORM_WRITE);

        cubeRoot.addChild(cubeRotate);
        cubeRotate.addChild(new ColorCube(0.4f));

        RocketBehavior rocketBehavior = new RocketBehavior(cubeRotate);
        rocketBehavior.setSchedulingBounds(new BoundingSphere());
        cubeRoot.addChild(rocketBehavior);

        cubeRoot.compile();

        add("Center", canvas);
        universe.getViewingPlatform().setNominalViewingTransform();
        universe.getViewer().getView().setBackClipDistance(100.0);
        universe.addBranchGraph(cubeRoot);
    }
}
