## Přehled: `pendulum_msfcn.m`

Tento soubor je S‑funkce (MATLAB S‑function) používaná v Simulink modelu `Pendulum`. Slouží jako spojka mezi numerickou implementací dynamiky vozík+kyvadlo a Simulinkem. S‑funkce definuje stavy systému, jejich počáteční hodnoty, výstupy a diferenciální rovnice (derivace).

Soubor NEobsahuje 3D animaci ani VR scénu — viz `Pendulum_VR.WRL` a Simulink model (`Pendulum.mdl`) pro propojení s VR. `pendulum_msfcn.m` je výhradně fyzikální model a rozhraní do Simulinku.

### Co je důležité (na co se zaměřit)
- Struktura S‑funkce: `setup`, `InitializeConditions`, `Outputs`, `Derivatives`, `CheckPrms`, `Terminate`.
- Pořadí spojitých stavů a jejich význam (velmi důležité pro kontrolní návrh a ladění):
  - `ContStates.Data(1)` = v  (rychlost vozíku)
  - `ContStates.Data(2)` = y  (pozice vozíku)
  - `ContStates.Data(3)` = w  (úhlová rychlost kyvadla)
  - `ContStates.Data(4)` = phi (úhel kyvadla, v radiánech)
- Jaké porty S‑funkce poskytuje:
  - 1 vstup: ovládací signál `u` (v kódu je to [V], vstupní napětí)
  - 2 výstupy: `y` (pozice) a `phi` převedené na stupně
- Dialogové parametry (`block.NumDialogPrms = 4`) — používají se při inicializaci. Podle kódu jsou to minimálně `x0` (počáteční pozice) a `phi0` (počáteční úhel v stupních), další dva parametry slouží jako příznaky (`obey_rail_bounds`, `cart_lock`).

### Co můžete upravovat (bezpečné a užitečné věci)
- Fyzikální konstanty a parametry (v `Derivatives` jsou sety konstant): `g, M, m, l, b, dlt, kf, u_max, u_ins` atd. Pokud chcete měnit fyziku modelu (hmotnosti, délku kyvadla, tření), upravte zde.
- Exponování některých konstant jako dialogových parametrů (pokud chcete upravovat z modelu bez editace .m souboru). Např. `M, m, l, b` by mohly být `block.DialogPrm(n)`.
- Výstupy: pokud chcete exportovat jiné signály, upravte `Outputs` (např. přidat výstup rychlosti nebo momentu).

### Co raději nechat být / co ignorovat
- Interní Simulink registrace metod v `setup` (to je S‑function boilerplate) — nechte být, pokud neznáte S‑funkce do hloubky.
- Detaily implementační algebra (např. definice zmíněných „lumped constants" `k1,k2,k3`) pokud neplánujete měnit model fyziky. Přemýšlejte spíše v termínech fyzikálních veličin (M, m, l, J) než v těchto mezivýpočtech.

### Důležité části k pochopení v kódu
- `CheckPrms`: kontroluje typ parametrů a omezí počáteční pozici (|x0| ≤ 0.91). Pokud budete měnit dialogové parametry, podívejte se sem.
- `InitializeConditions`: nastavuje počáteční stavy (pozn.: `phi0` je v souboru uložen ve stupních a přepočítán na radiány zde).
- `Derivatives`: obsahuje samotné diferenciální rovnice. Hledejte:
  - saturaci vstupu (`u_max`) a deadzone (`u_ins`)
  - „rail bounds" (hranice kolejnice) a chování při nárazu: pokud `obey_rail_bounds` a vozík dosáhne hranice, model nastaví velké tlumení `-300*v` a zruší vstup
  - `cart_lock` režim, který úplně zamkne vozík

### Numerické a bezpečnostní poznámky
- Denominátor při výpočtu `dv` a `d3` je `k1*k3*sin(phi)^2 - 1`. Dávejte pozor na situace, kde tento výraz může vést k dělení malým číslem nebo blízko nule — to může způsobit velké derivace a numerickou nestabilitu.
- Při návrhu řadiče dejte pozor na saturaci: vstup je limitován `u_max` a má deadzone `u_ins`.
- Pokud simulace hlučí (hodně oscilací), zkontrolujte nastavení solveru v Simulinku (`ode45`, krok, `RelTol`) a případně přejděte na tučnější nebo stiff solver.

### Jak ladit / jak testovat změny
1. Nechte model v Simulinku a přidejte Scope bloky na výstupy S‑funkce (`y` a `phi`) a případně na vstup `u`.
2. Dělejte malé změny parametrů (např. `b` nebo `dlt`) a sledujte odezvu. Po každé změně spusťte krátkou simulaci (např. StopTime = 5s).
3. Pokud přidáte nové dialogové parametry, restartujte Simulink nebo znovu načtěte S‑funkci (u S‑funkcí někdy potřebujete překompilovat/ znovu načíst model).

### Doporučené malé vylepšení (nejsou nutné, ale užitečné)
- Přesunout fyzikální konstanty do dialogových parametrů nebo externího `.mat` souboru — usnadní to ladění bez změny kódu.
- Přidat kontrolní asserts / ochrany v `Derivatives` pro bezpečné chování při singulárních stavech (např. omezit maximální |dv|).
- Dokumentovat jednotky (v hlavičce souboru doplňte komentář s jednotkami pro každou veličinu).

### Rychlé shrnutí — co řešit jako první
1. Pokud chcete ladit řízení: zaměřte se na výstupy (y, phi) a na saturaci vstupu `u_max`/`u_ins`.
2. Pokud chcete změnit fyziku: upravte `M, m, l, b, dlt` v `Derivatives` nebo udělejte z nich dialogové parametry.
3. Pokud chcete VR nebo vizualizaci: nechte `Pendulum_VR.WRL` beze změn a propojování řeší Simulink model (bloky VR Sink/Source), ne tato .m S‑funkce.

Pokud chcete, mohu: vygenerovat krátký MATLAB skript, který na základě parametrů ze souboru spustí simulaci modelu (pokud máte MATLAB), nebo upravit S‑funkci tak, aby vystavovala více parametrů jako dialogové parametry. Kterou z těchto možností preferujete?
