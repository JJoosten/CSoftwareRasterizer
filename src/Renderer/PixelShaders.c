#include "PixelShaders.h"

RGBA8 DefaultPixelShader( const void* const uniforms)
{
  DefaultPixelShaderUniforms* psUniforms = (DefaultPixelShaderUniforms*)uniforms;

  return 0xFF0000FF;
}
