package devtitans.smartgasmanager;

import android.util.Log;
import android.os.ServiceManager;
import android.os.IBinder;
import android.os.RemoteException;

import devtitans.smartgas.ISmartgas;                      // Criado pelo AIDL

public class SmartgasManager {
    private static final String TAG = "DevTITANS.SmartgasManager";
    private IBinder binder;
    private ISmartgas service;

    private static SmartgasManager instance;

    // Construtor. Configura a "instância da classe" (objeto) recém-criada. 
    // Note o "private" no construtor. Essa classe só pode ser instanciada dentro desse arquivo.
    private SmartgasManager() {
        Log.d(TAG, "Nova (única) instância do SmartgasManager ...");

        binder = ServiceManager.getService("devtitans.smartgas.ISmartgas/default");
        if (binder != null) {
            service = ISmartgas.Stub.asInterface(binder);
            if (service != null)
                Log.d(TAG, "Serviço Smartgas acessado com sucesso.");
            else
                Log.e(TAG, "Erro ao acessar o serviço Smartgas!");
        }
        else
            Log.e(TAG, "Erro ao acessar o Binder!");
    }

    // Acessa a (única) instância dessa classe. Se ela não existir ainda, cria.
    // Note o "static" no método. Podemos executá-lo sem precisar instanciar um objeto.
    public static SmartgasManager getInstance() {
        if (instance == null)
            instance = new SmartgasManager();

        return instance;
    }

    public int connect() throws RemoteException {
        Log.d(TAG, "Executando método connect() ...");
        return service.connect();
    }

    public int getConcentration() throws RemoteException {
        Log.d(TAG, "Executando método getConcentration() ...");
        return service.getConcentration();
    }
}