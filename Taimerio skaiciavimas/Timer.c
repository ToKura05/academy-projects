
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

/*Si programa skirta sukurti optimalius taimerio skaiciavimus prescaleriui ir ARR registrui.
Lygtis: Evento daznis = sysclock/(prescaler+1)(ARR+1)
Evento periodas = (prescaler+1)(ARR+1)/sysclock =====> ARR + 1 = (periodas*sysclock)/(mult*prescaler+1)
Programa turetu paimti norima dazni ir norima prescalerio reiksme
Sekmes, tamsta! */

int main()
{
    int sysclock = 72000000; //kaip pvz
    int prescaler;
    int reload;
    float event;
    int flag=0;
    char mode,units;
    int multiplier;
    printf("Hello. Tavo sysclock daznis yra %d. Pasirinkite rezima:\n1 Daznis\n2 Periodas\n3 Exit\n",sysclock);
    scanf(" %c",&mode);

    if(mode=='1')
    {
        printf("Kokio daznio evento nori?\n");
        scanf(" %f",&event);
    }
    else if (mode=='2')
    {
        printf("Pasirink laiko vienetus:\n1 s\n2 ms\n3 us\n");
        scanf(" %c",&units);
        switch(units)
        {
        case '2':
            multiplier=1000;
            break;
        case '3':
            multiplier=1000000;
            break;
        default:
            multiplier=1;
            break;
        }
        printf("Kas kiek laiko evento nori?\n");
        scanf(" %f",&event);
    }
    else
        return 0;

    while(flag==0)
    {
        printf("Gal galetum daugiau maziau parasyti prescalerio verte?\n");
        do
        {
            scanf(" %d",&prescaler);
            if (prescaler>65536 || prescaler<0)
                printf("Per didele (maza) verte! Bandyk is naujo.\n");
        }
        while (prescaler>65536 || prescaler<0);

        if(mode=='2')
            reload=(sysclock*event)/(prescaler*multiplier);
        else
            reload=sysclock/(prescaler*event);

        if (reload>65535)
        {
            printf("Pasirodo per maza prescalerio reiksme. Bandyk viska is naujo.\n");
        }
        else
        {
            printf("Tavo suskaiciuotas reloadas: %d\n",reload);
            flag=1;
        }

    }
    printf("VALIO! Pavyko nusistatyt viska. I savo parametrus rasyk: PRESCALER = %d, PERIOD = %d. Geros dienos!",prescaler-1,reload-1);

    return 0;
}
