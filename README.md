**Simple FPS Prototype**

A lightweight First-Person Shooter (FPS) prototype built in Unreal Engine, focusing on core movement mechanics, weapon handling, and dynamic tactical AI. This project serves as a demonstration of basic gameplay loops, custom asset integration, and hybrid C++/Blueprint architecture.

## 🎮 Features

### Combat Mechanics
* **Shooting System:** Hitscan/projectile logic with line tracing.
* **Reload Mechanism:** Functional ammo counting and reload logic.
* **Weapon Sway:** Procedural mouse sway animation to add weight and realism to the weapon movement while looking around.
* **Enemy Damage & Ragdoll:** Patrolling enemies react to hitscan damage, complete with health states and physics-based ragdoll deaths.

### Tactical AI (Utility System)
* **Dynamic Cover Scoring:** A custom-built Utility AI system that calculates the safest cover spots in real-time during a firefight.
* **Line-of-Sight (LoS) Raycasting:** AI dynamically shoots raycasts to active enemies to determine if a cover position is exposed or safe.
* **"King of the Hill" Math:** Cover spots are scored based on variables like enemy proximity, number of exposed angles, and run-distance penalties.
* **Asynchronous "Bail Out" Logic:** AI constantly double-checks its destination while running and dynamically changes routes if a patrolling enemy suddenly gains line of sight.

### Engine Systems & C++
* **Simple Graphics Setting UI:** Written natively in C++ for optimal performance.
* **LLM API Foundation:** Includes a custom C++ HTTP module (`MyAIActor`) designed to securely parse JSON payloads and communicate directly with external APIs (like Gemini) without relying on third-party plugins.
* **Chaos Destruction:** Integration of Unreal's Chaos physics system for dynamically fracturing destructible environmental cover.

### Animation & Assets
* **Custom Weaponry:** The gun model was rigged from scratch in Blender before being imported into Unreal Engine.
* **Custom Animations:** Includes bespoke animations for firing, reloading, and idle states seamlessly blended via AnimMontages and State Machines.

### Video

https://github.com/user-attachments/assets/6a807a6a-373e-455a-b081-627a16b800ae

https://github.com/user-attachments/assets/9fabc8dc-68ac-4540-b332-f3c9b1885c30


### Screenshots

<img width="1920" height="1080" alt="Snapshot_2" src="https://github.com/user-attachments/assets/f4c41112-5cad-49a8-8354-ef814a8c85cb" />

<img width="1920" height="1080" alt="Snapshot_1" src="https://github.com/user-attachments/assets/229f6e2b-38f3-4fe5-aa72-34cecb83a1d5" />


