use uo;
use os;

include "include/client";
include ":attributes:attributes";

function summon_creature( caster, circle := 8, npctemplate, cast_loc, gate)
  var thecreature;
  var thecritter;
  var magery := AP_GetSkill(caster, MAGERY);
  var duration := 20 + (magery * 2);
  var parms := struct;
  parms .+ script := "tamed";
  Detach();
  sleep(2);
  thecritter := CreateNpcFromTemplate(npctemplate, 5849, 1207, 0, parms, caster.realm);
  if(npctemplate == "demon")
    thecritter.setCriminal(1);w
    caster.setCriminal(1);
  endif
  MoveObjectToLocation(thecritter, cast_loc.x, cast_loc.y, cast_loc.z, thecritter.realm, MOVEOBJECT_FORCELOCATION);
  sleepms(500);
  DestroyItem(gate);
  SetObjProperty(thecritter,"master", caster.serial);
  SetScriptController( thecritter);
  SetObjProperty(thecritter, "happiness",100);
  SetObjProperty(thecritter, "summoned",1);
  RestartScript(thecritter);
  AP_SetTrueSkill( thecritter, RESISTING_SPELLS,  magery*10  );
  PlaySoundEffect(caster, SFX_SPELL_SUMMON_ELEMENTAL);
  sleep(duration);
  PlaySoundEffect( thecritter, SFX_SPELL_MANA_VAMPIRE );
  PlayStationaryEffect( thecritter.x, thecritter.y, thecritter.z, FX_SMOKE, 0xa, 0xa, 0, thecritter.realm );
  MoveObjectToLocation(thecritter,0,0,0,"britannia_alt",MOVEOBJECT_FORCELOCATION);
  Damage(thecritter, GetHp(thecritter) + 3);
endfunction

