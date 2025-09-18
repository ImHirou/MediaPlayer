import QtQuick 2.15

ShaderEffect {
    id: rounding
    anchors.centerIn: parent

    property real radius: 20
    property Item srcItem
    
    property variant src: ShaderEffectSource {
        sourceItem: rounding.srcItem
        hideSource: true
        live: true
        recursive: true
    }

    property real u_width: srcItem ? srcItem.width : 0
    property real u_height: srcItem ? srcItem.height : 0

    width: u_width
    height: u_height

    fragmentShader: "
        varying vec2 qt_TexCoord0;
        uniform sampler2D src;
        uniform float radius;
        uniform float u_width;
        uniform float u_height;

        void main() {
            vec2 uv = qt_TexCoord0;

            vec2 p = vec2(uv.x * u_width, uv.y * u_height);

            vec2 rectMin = vec2(radius, radius);
            vec2 rectMax = vec2(u_width - radius, u_height - radius);

            vec2 clamped = clamp(p, rectMin, rectMax);

            float dist = length(p - clamped);

            float aa = 1.0;

            float alphaMask = 1.0 - smoothstep(radius - aa, radius + aa, dist);

            vec4 color = texture2D(source, uv);
            color.a *= alphaMask;

            gl_FragColor = color;
        }"
}
