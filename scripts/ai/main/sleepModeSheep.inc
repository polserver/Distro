include ":attributes:attributes";
function sleepmode()
  foreach critter in ListMobilesNearLocation( me.x,me.y,me.z, 15, me.realm);
    if(!critter.isA(POLCLASS_NPC))
      look_around();
      break;
    endif
  endforeach
  if(GetObjProperty(me,"killme"))
    SetObjProperty(me, "guardkill", 1);
    MoveObjectToLocation(me, 5276, 1185, 0, "britannia_alt", MOVEOBJECT_FORCELOCATION);
    ApplyRawDamage(me, GetHp(me)+1);
  endif
  EraseObjProperty(me,"#flees");
  DisableMainEvents();
  if(AP_GetSkill(me, HIDING) > 0 )
    me.hidden := 1;
  endif
  EnableEvents(SYSEVENT_ENTEREDAREA,18);
  EnableEvents(SYSEVENT_ENGAGED);
  EnableEvents(SYSEVENT_DAMAGED);
  var ev;
  EnableEvents(SYSEVENT_DOUBLECLICKED);
  while (1)
    ev := os::wait_for_event(30);
    repeat
    if(RandomInt(1) == 1)
      PlaySoundEffect(me, idlesnd1);
    else
      PlaySoundEffect(me, idlesnd2);
    endif
    case (ev.type)
      SYSEVENT_DOUBLECLICKED: if(((RandomInt(499) + 1) == 250) || (ev.source.cmdlevel >= 3))
                                PlaySoundEffect(me, SFX_SPELL_EXPLOSION);
                                PlayStationaryEffect(me.x, me.y, me.z, FX_EXPLODE_3, 7, 0x10, 0, me.realm);
                                sleepms(5);
                                MoveObjectToLocation(me,0,0,0, "britannia_alt", MOVEOBJECT_FORCELOCATION);
                                ApplyRawDamage(me, GetHp(me) + 3);
                              endif
      SYSEVENT_ENGAGED:    if((!(ev.source).npctemplate) || (((ev.source).script == "employed") || ((ev.source).script == "tamed")))
                             if (me.hidden)
                               me.hidden := 0;
                             endif
                             EnableMainEvents();
                             return ev;
                           endif
      SYSEVENT_DAMAGED:    if((!(ev.source).npctemplate) || (((ev.source).script == "employed") || ((ev.source).script == "tamed")))
                             if (me.hidden)
                               me.hidden := 0;
                             endif
                             EnableMainEvents();
                             return ev;
                           endif
      EVID_ALL_ATTACK_CMD: if(me.hidden)
                             me.hidden := 0;
                           endif
                           EnableMainEvents();
                           return ev;
      SYSEVENT_ENTEREDAREA: if((!(ev.source).npctemplate) || (((ev.source).script == "employed") || ((ev.source).script == "tamed")))
                             if(me.hidden)
                               me.hidden := 0;
                             endif
                             EnableMainEvents();
                             return ev;
                           endif
      EVID_HERDING:        Herd(ev);
    endcase
    until(!(ev := os::wait_for_event(30)));
  endwhile
endfunction