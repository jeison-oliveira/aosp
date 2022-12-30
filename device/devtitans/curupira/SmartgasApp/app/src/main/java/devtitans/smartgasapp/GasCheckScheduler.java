package devtitans.smartgasapp;

import android.app.AlarmManager;
import android.app.PendingIntent;
import android.content.Context;
import android.content.Intent;

public class GasCheckScheduler {

    public static void scheduleGasCheck(Context context) {
        AlarmManager manager = context.getSystemService(AlarmManager.class);
        Intent intent = new Intent("devtitans.smartgasapp.SMARTGAS_BROADCAST");
        manager.setInexactRepeating(AlarmManager.RTC_WAKEUP, 61000, 61000, PendingIntent.getService(context, 1, intent, PendingIntent.FLAG_IMMUTABLE));
    }
}
