//
//  Shader.fsh
//  Interface
//
//  Created by Jiman Jeong on 13. 8. 16..
//  Copyright (c) 2013년 SOC. All rights reserved.
//

varying lowp vec4 colorVarying;

void main()
{
    gl_FragColor = colorVarying;
}
