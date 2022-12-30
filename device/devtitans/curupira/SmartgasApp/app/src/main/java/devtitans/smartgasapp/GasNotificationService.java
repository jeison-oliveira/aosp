package devtitans.smartgasapp;

import android.app.IntentService;
import android.app.NotificationChannel;
import android.app.NotificationManager;
import android.app.PendingIntent;
import android.content.Context;
import android.content.Intent;
import android.media.RingtoneManager;
import android.os.RemoteException;
import android.util.Log;

import androidx.annotation.Nullable;
import androidx.core.app.NotificationCompat;

import devtitans.smartgasmanager.SmartgasManager;

public class GasNotificationService extends IntentService {

    public GasNotificationService() {
        super("SmartGasAlarmService");
    }

    public void showNotification(Context context, String title, String message, Intent intent, int reqCode) {
        PendingIntent pendingIntent = PendingIntent.getActivity(context, reqCode, intent, PendingIntent.FLAG_ONE_SHOT | PendingIntent.FLAG_IMMUTABLE);
        String CHANNEL_ID = "channel_name";// The id of the channel.
        NotificationCompat.Builder notificationBuilder = new NotificationCompat.Builder(context, CHANNEL_ID)
                .setSmallIcon(R.mipmap.ic_launcher)
                .setContentTitle(title)
                .setContentText(message)
                .setAutoCancel(true)
                .setSound(RingtoneManager.getDefaultUri(RingtoneManager.TYPE_NOTIFICATION))
                .setContentIntent(pendingIntent);
        NotificationManager notificationManager = (NotificationManager) context.getSystemService(Context.NOTIFICATION_SERVICE);
        CharSequence name = "SmartGas";// The user-visible name of the channel.
        int importance = NotificationManager.IMPORTANCE_HIGH;
        NotificationChannel mChannel = new NotificationChannel(CHANNEL_ID, name, importance);
        notificationManager.createNotificationChannel(mChannel);
        notificationManager.notify(reqCode, notificationBuilder.build()); // 0 is the request code, it should be unique id
    }

    @Override
    protected void onHandleIntent(@Nullable Intent intent) {
        try {
            int concentration = SmartgasManager.getInstance().getConcentration();
            Log.d("smartgas", "concentration = " + concentration);
            if (concentration > 1000) {
                Log.d("smartgas", "ALTA CONCENTRAÇÃO DE GÁS!!");
                Intent i = new Intent(this, MainActivity.class);
                showNotification(this, "SmartGasApp", "ALTA CONCENTRAÇÃO DE GÁS!", i, 1);
            } else {
                Log.d("smartgas", "Baixa concentração de gás");
            }
        } catch (RemoteException e) {
            e.printStackTrace();
        }
    }
}
