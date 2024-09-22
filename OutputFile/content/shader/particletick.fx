#ifndef _PARTICLE_TICK
#define _PARTICLE_TICK

#include "value.fx"
#include "struct.fx"

RWStructuredBuffer<tParticle> ParticleBuffer : register(u0);
RWStructuredBuffer<tSpawnCount> SpawnCountBuffer : register(u1);

#define MAX_COUNT       g_int_0
#define Particle        ParticleBuffer[_ID.x]

[numthreads(1024, 1, 1)]
void CS_ParticleTick(int3 _ID : SV_DispatchThreadID)
{
    if (MAX_COUNT <= _ID.x)
        return;
    
    if (false == Particle.Active)
    {
        int SpawnCount = SpawnCountBuffer[0].iSpawnCont;
                
        while (0 < SpawnCount)
        {
            int Origin = 0;
                        
            //InterlockedExchange(  SpawnCountBuffer[0].iSpawnCont
            //                    , SpawnCountBuffer[0].iSpawnCont - 1
            //                    , Origin);
            
            InterlockedCompareExchange(SpawnCountBuffer[0].iSpawnCont
                                      , SpawnCount
                                      , SpawnCountBuffer[0].iSpawnCont - 1
                                      , Origin);

            if (SpawnCount == Origin)
            {
                Particle.Active = true;
                break;
            }
            
            SpawnCount = SpawnCountBuffer[0].iSpawnCont;
        }
    }
    else
    {
        
        Particle.vWorldPos += Particle.vVelocity * g_EngineDT;
    }
    
}

// 1. 파티클 렌더링, 비활성화 파티클 처리 + 빌보드
// 2. 파티클 스레드 동기화
// 3. 파티클 CS 에서 랜덤.







#endif