(ns cljweb.core
  (:require [org.httpkit.server :as s]
            [compojure.core :refer [routes POST GET ANY]]))

(defonce ^:private server (atom nil))

(defn remove-trailing-slash [handler]
  (fn [req]
    (let [uri (:uri req)
          not-root? (not= uri "/")
          ends-with-slash? (.endsWith ^String uri "/")
          fixed-uri (if (and not-root?
                             ends-with-slash?)
                      (clojure.string/replace uri #"/*$" "")
                      uri)
          fixed-req (assoc req :uri fixed-uri)]
          (handler fixed-req))))

(defn stop-server []
  (when-not (nil? @server)
    ;; graceful shutdown: wait 100ms for existing requests to be finished
    ;; :timeout is optional, when no timeout, stop immediately
    (@server :timeout 100)
    (reset! server nil)))

(defn app []
  (routes 
    (GET "/" [:as req]
         {:status 200
          :headers {"Context/Type" "text/html"}
          :body "<h1>Hi from root!</h1>"})
    (GET "/:user-name" [user-name :as req]
         {:status 200
          :headers {"Context/Type" "text/html"}
          :body (format "<h1>Hi from %s</h1>" user-name)})))

(defn create-server []
  (s/run-server (remove-trailing-slash (app)) {:ip "0.0.0.0" :port 4000}))

(defn run-server []
  (reset! server (create-server)))

(stop-server)
(run-server)

