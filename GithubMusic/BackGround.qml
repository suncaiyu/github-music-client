import QtQuick 2.0
import QtQuick.Particles 2.14

Item {
    ParticleSystem{
        id: sys
    }

    ImageParticle{
        color : "green"
        system: sys
        source: "qrc:/font/res/star.png"
        colorVariation: 0.8
        rotation: 15
        rotationVariation: 5
        rotationVelocity: 45
        rotationVelocityVariation: 15
        entryEffect: ImageParticle.Scale
    }

    Emitter{

        id: startField
        system: sys

        emitRate: 60
        lifeSpan: 3500
        lifeSpanVariation: 3500

        width: ww.width
        height: ww.height

        //acceleration: PointDirection { xVariation: 200; yVariation: 200; }

        size: 0
        endSize: 40
        sizeVariation: 5
        velocity: AngleDirection{
            angle: 0
            angleVariation: 15
            magnitude: 100
            magnitudeVariation: 50
        }
    }
}
